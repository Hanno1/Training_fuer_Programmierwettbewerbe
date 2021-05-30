from scanner import Scanner
import csv


class Parser:
    def __init__(self, data_in):
        self.input = data_in
        self.scanner = Scanner(self.input)
        self.desc = None
        self.ident = None
        self.get_sym()
        self.fnumber()

    def fnumber(self):
        if self.desc == 'minus' or self.desc == 'plus':
            self.get_sym()
        if self.desc == 'constant':
            self.get_sym()
            if self.desc == 'point':
                self.get_sym()
                if self.desc == 'constant':
                    self.get_sym()
                else:
                    self.error('constant')
            if self.desc != "none":
                self.exponent()
        else:
            self.error('constant')

    def exponent(self):
        if self.desc == "exp":
            self.get_sym()
            if self.desc == 'plus' or self.desc == 'minus':
                self.get_sym()
            if self.desc == 'constant':
                self.get_sym()
            else:
                self.error('constant')
        else:
            self.error('exp')

    def get_sym(self):
        self.desc, self.ident = self.scanner.get_sym()

    def description_equals(self, symbol):
        return self.desc == symbol

    def error(self, expected):
        raise Exception(f"Expected '{expected}', found {self.ident}")


if __name__ == "__main__":
    test_cases = []
    with open("samples_fnumber.txt") as csv_file:
        reader = csv.reader(csv_file, delimiter=",")
        for row in reader:
            test_cases.append(row[0])

    for test_case in test_cases:
        expr = test_case
        p = Parser(expr)
    print("Tests successfully")
