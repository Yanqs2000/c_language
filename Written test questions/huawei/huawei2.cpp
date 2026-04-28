#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

// 定义设备数据的结构体，方便存储和管理
struct DeviceData
{
    std::string id;
    std::vector<double> features; // 5个特征: 写次数, 读次数, 平均写延迟, 平均读延迟, 设备使用年限
    int status;                   // 状态: 0正常, 1故障
    std::vector<bool> is_nan;     // 标记原始数据中哪些特征是"NaN"

    // 构造函数
    DeviceData() : features(5), is_nan(5, false), status(-1) {}
};

// 工具函数：根据特征索引和值判断是否为异常值
bool is_outlier(int feature_idx, double value)
{
    switch (feature_idx)
    {
    case 0:
        return value < 0; // 写入次数
    case 1:
        return value < 0; // 读取次数
    case 2:
        return value < 0 || value > 1000; // 平均写入延迟
    case 3:
        return value < 0 || value > 1000; // 平均读取延迟
    case 4:
        return value < 0 || value > 20; // 设备使用年限
    default:
        return false;
    }
}

// 工具函数：解析一行CSV格式的数据
DeviceData parse_line(const std::string &line, bool is_training_data)
{
    DeviceData data;
    std::stringstream ss(line);
    std::string item;

    // 1. 解析设备ID
    std::getline(ss, item, ',');
    data.id = item;

    // 2. 解析5个特征值
    for (int i = 0; i < 5; ++i)
    {
        std::getline(ss, item, ',');
        if (item == "NaN")
        {
            data.is_nan[i] = true;
            data.features[i] = 0.0; // 先用0占位，后续会填充
        }
        else
        {
            try
            {
                data.features[i] = std::stod(item);
            }
            catch (const std::invalid_argument &e)
            {
                data.is_nan[i] = true;
                data.features[i] = 0.0;
            }
            catch (const std::out_of_range &e)
            {
                // 如果数值过大或过小，也可以当作缺失值处理
                data.is_nan[i] = true;
                data.features[i] = 0.0;
            }
        }
    }

    // 3. 如果是训练数据，解析状态值
    if (is_training_data)
    {
        std::getline(ss, item, ',');
        if (!item.empty())
            data.status = std::stoi(item);
    }
    return data;
}

int main()
{
    // 提高C++ I/O效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // --- 1. 读取和解析训练数据 ---
    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 消耗掉cin留下的换行符

    std::vector<DeviceData> training_data;
    training_data.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        std::string line;
        std::getline(std::cin, line);
        training_data.push_back(parse_line(line, true));
    }

    // --- 2. 数据清洗 ---
    // a) 从训练数据中计算用于填充的均值和中位数
    std::vector<double> means(5);
    std::vector<double> medians(5);

    for (int j = 0; j < 5; ++j)
    {
        std::vector<double> valid_values;
        for (const auto &data : training_data)
        {
            // 只使用非NaN且非异常的值来计算统计量
            if (!data.is_nan[j] && !is_outlier(j, data.features[j]))
            {
                valid_values.push_back(data.features[j]);
            }
        }

        if (valid_values.empty())
        {
            means[j] = 0.0;
            medians[j] = 0.0;
        }
        else
        {
            // 计算均值
            double sum = std::accumulate(valid_values.begin(), valid_values.end(), 0.0);
            means[j] = sum / valid_values.size();

            // 计算中位数 (*** 这是关键的修正点 ***)
            std::sort(valid_values.begin(), valid_values.end());
            size_t size = valid_values.size();
            if (size % 2 == 1)
            {
                // 如果数量为奇数，中位数是中间的那个数
                medians[j] = valid_values[size / 2];
            }
            else
            {
                // 如果数量为偶数，中位数是中间两个数的平均值
                medians[j] = (valid_values[size / 2 - 1] + valid_values[size / 2]) / 2.0;
            }
        }
    }

    // b) 应用清洗规则，填充训练数据
    for (auto &data : training_data)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (data.is_nan[j])
            {
                data.features[j] = means[j];
            }
            else if (is_outlier(j, data.features[j]))
            {
                data.features[j] = medians[j];
            }
        }
    }

    // --- 3. 逻辑回归模型训练 (Batch Gradient Descent) ---
    std::vector<double> w(6, 0.0); // w[0]是偏置项w0, w[1]..w[5]是特征权重
    double alpha = 0.01;
    int iterations = 100;

    for (int iter = 0; iter < iterations; ++iter)
    {
        std::vector<double> gradients(6, 0.0);

        // 遍历所有样本计算梯度总和
        for (const auto &sample : training_data)
        {
            // z = w0 + w1*x1 + ... + w5*x5
            double z = w[0];
            for (int j = 0; j < 5; ++j)
            {
                z += w[j + 1] * sample.features[j];
            }

            // p = sigmoid(z)
            double p = 1.0 / (1.0 + exp(-z));

            // error = p - y_true
            double error = p - sample.status;

            // 累加梯度
            gradients[0] += error; // 偏置项的梯度
            for (int j = 0; j < 5; ++j)
            {
                gradients[j + 1] += error * sample.features[j];
            }
        }

        // 使用平均梯度更新权重
        for (int j = 0; j < 6; ++j)
        {
            w[j] -= alpha * gradients[j] / n;
        }
    }

    // --- 4. 预测输出 ---
    int m;
    std::cin >> m;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < m; ++i)
    {
        std::string line;
        std::getline(std::cin, line);

        // a) 解析预测数据
        DeviceData test_data = parse_line(line, false);

        // b) 使用从训练数据得到的统计量来清洗预测数据
        for (int j = 0; j < 5; ++j)
        {
            if (test_data.is_nan[j])
            {
                test_data.features[j] = means[j];
            }
            else if (is_outlier(j, test_data.features[j]))
            {
                test_data.features[j] = medians[j];
            }
        }

        // c) 进行预测
        double z = w[0];
        for (int j = 0; j < 5; ++j)
        {
            z += w[j + 1] * test_data.features[j];
        }

        // d) 根据预测规则输出结果: P(y=1) >= 0.5  等价于 z >= 0
        if (z >= 0)
        {
            std::cout << 1 << "\n";
        }
        else
        {
            std::cout << 0 << "\n";
        }
    }

    return 0;
}
