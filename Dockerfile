FROM alpine:latest AS builder

RUN apk add --no-cache g++

WORKDIR /app

COPY compiler.cpp .

RUN g++ compiler.cpp -std=c++17 -static -o compiler


FROM alpine:latest

WORKDIR /app


COPY --from=builder /app/compiler .


COPY input.txt .

CMD ["./compiler"]