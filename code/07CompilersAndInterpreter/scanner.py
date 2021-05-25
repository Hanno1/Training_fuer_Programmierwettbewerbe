import string


class Input:
    def __init__(self, data_in):
        self.index = 0
        self.length = len(data_in)
        self.input = data_in

    def next(self):
        if self.index < self.length:
            literal = self.input[self.index]
            self.index += 1
            return literal
        else:
            return None


DIGIT = [str(i) for i in range(10)]
SYMBOLS = {'+': 'plus', '-': 'minus', '.': 'point'}


class Scanner:
    def __init__(self, data_in):
        self.input = Input(data_in)
        self.current = self.input.next()

    def get_sym(self):
        identifier = ""
        description = ""
        while self.current == " ":
            self.current = self.input.next()

        # Constant
        if self.current in DIGIT:
            description = "constant"
            identifier = self.current
            self.current = self.input.next()
            while self.current in DIGIT:
                identifier += self.current
                self.current = self.input.next()

        # Symbol
        elif self.current in SYMBOLS.keys():
            description = SYMBOLS.get(self.current)
            identifier = self.current
            self.current = self.input.next()

        # Function
        elif self.current == "E" or self.current == "e":
            description = "E"
            identifier = "E"
            self.current = self.input.next()
            if self.current == "e" or self.current == "E":
                # prob not necessary since we can catch this using the parser
                raise Exception("Too many E's")

        elif self.current is None:
            description = "none"
            identifier = self.current

        else:
            raise Exception(f"Unknown Symbol: {self.current}")

        return description, identifier


if __name__ == "__main__":
    expr = "-123.12e99"
    scanner = Scanner(expr)
    desc, ident = scanner.get_sym()
    while ident:
        print(f"({desc}, {ident})")
        desc, ident = scanner.get_sym()
