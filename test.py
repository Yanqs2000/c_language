class NumberOperations:  
    def __init__(self, num):  
        self.num = num  
  
    def add_one(self):  
        self.num += 1  
        return self.num  
  
    def subtract_one(self):  
        self.num -= 1  
        return self.num  
  
    def multiply_by_two(self):  
        self.num *= 2  
        return self.num  
  
    def divide_by_two(self):  
        # 注意：这里假设我们总是处理非零数  
        if self.num != 0:  
            self.num /= 2  
            return self.num  
        else:  
            return "Error: Cannot divide by zero"  
  
# 使用示例  
operations = NumberOperations(5)  
print(operations.add_one())       # 输出: 6  
print(operations.subtract_one())  # 输出: 5  
print(operations.multiply_by_two())  # 输出: 10  
print(operations.divide_by_two())  # 输出: 5.0  