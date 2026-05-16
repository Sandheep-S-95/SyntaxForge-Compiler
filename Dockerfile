# Stage 1: The Builder (Uses tiny Alpine Linux)
FROM alpine:latest AS builder

# Install g++ quickly via Alpine's package manager
RUN apk add --no-cache g++

WORKDIR /app

# Step A: Copy ONLY the C++ file first. 
# This ensures Docker only recompiles if compiler.cpp actually changes.
COPY compiler.cpp .

# Step B: Compile statically so it can run anywhere without extra libraries
RUN g++ compiler.cpp -std=c++17 -static -o compiler

# Stage 2: The Runner (Super tiny final image)
FROM alpine:latest

WORKDIR /app

# Copy only the finished binary from the builder stage
COPY --from=builder /app/compiler .

# Copy your input file (your C++ code looks for "input.txt" in the current dir)
COPY input.txt .

CMD ["./compiler"]