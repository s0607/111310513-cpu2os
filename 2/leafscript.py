# Lexer：詞法分析器
# =========================

def tokenize(code):
    token_rules = [
        ("NUMBER", r"\d+"),
        ("ID", r"[A-Za-z_][A-Za-z0-9_]*"),
        ("OP", r"==|!=|>=|<=|[+\-*/=<>]"),
        ("LBRACE", r"\{"),
        ("RBRACE", r"\}"),
        ("SEMI", r";"),
        ("SKIP", r"[ \t\n]+"),
    ]

    regex = "|".join(f"(?P<{name}>{pattern})" for name, pattern in token_rules)
    tokens = []

    for match in re.finditer(regex, code):
        kind = match.lastgroup
        value = match.group()

        if kind != "SKIP":
            tokens.append((kind, value))

    return tokens


# =========================
# Interpreter：解譯器
# =========================

class LeafScript:
    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0
        self.variables = {}

    def peek(self):
        if self.pos < len(self.tokens):
            return self.tokens[self.pos]
        return None

    def eat(self, expected_value=None):
        token = self.peek()

        if token is None:
            raise Exception("程式碼結束太早")

        if expected_value is not None and token[1] != expected_value:
            raise Exception(f"語法錯誤：預期 {expected_value}，但得到 {token[1]}")

        self.pos += 1
        return token

    def run(self):
        while self.peek() is not None:
            self.statement()

    def statement(self):
        token = self.peek()

        if token[1] == "let":
            self.let_statement()

        elif token[1] == "print":
            self.print_statement()

        elif token[1] == "if":
            self.if_statement()

        elif token[1] == "while":
            self.while_statement()

        else:
            self.assign_statement()

    def let_statement(self):
        self.eat("let")
        name = self.eat()[1]
        self.eat("=")

        expr = self.read_expression_until(";")
        value = self.eval_expression(expr)

        self.variables[name] = value
        self.eat(";")

    def assign_statement(self):
        name = self.eat()[1]
        self.eat("=")

        expr = self.read_expression_until(";")
        value = self.eval_expression(expr)

        self.variables[name] = value
        self.eat(";")

    def print_statement(self):
        self.eat("print")

        expr = self.read_expression_until(";")
        value = self.eval_expression(expr)

        print(value)
        self.eat(";")

    def if_statement(self):
        self.eat("if")

        condition = self.read_expression_until("{")
        self.eat("{")

        block = self.collect_block()

        if self.eval_expression(condition):
            child = LeafScript(block)
            child.variables = self.variables
            child.run()

    def while_statement(self):
        self.eat("while")

        condition = self.read_expression_until("{")
        self.eat("{")

        block = self.collect_block()

        while self.eval_expression(condition):
            child = LeafScript(block)
            child.variables = self.variables
            child.run()

    def read_expression_until(self, stop_symbol):
        expr = []

        while self.peek() is not None and self.peek()[1] != stop_symbol:
            expr.append(self.eat()[1])

        return " ".join(expr)

    def collect_block(self):
        depth = 1
        block = []

        while depth > 0:
            token = self.eat()

            if token[1] == "{":
                depth += 1

            elif token[1] == "}":
                depth -= 1

                if depth == 0:
                    break

            block.append(token)

        return block

    def eval_expression(self, expr):
        for name, value in self.variables.items():
            expr = re.sub(rf"\b{name}\b", str(value), expr)

        try:
            return eval(expr)
        except Exception:
            raise Exception(f"運算錯誤：{expr}")


# =========================
# 主程式
# =========================

if __name__ == "__main__":
    code = """
let x = 1;
let sum = 0;

while x <= 5 {
    sum = sum + x;
    x = x + 1;
}

print sum;
"""

    tokens = tokenize(code)

    interpreter = LeafScript(tokens)

    interpreter.run()
