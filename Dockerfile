FROM ubuntu:24.04 AS build

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    libdrogon-dev \
    libjsoncpp-dev \
    libpq-dev \
    pkg-config \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY CMakeLists.txt ./
COPY src ./src

RUN cmake -S . -B build && cmake --build build -j

FROM ubuntu:24.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    libdrogon-dev \
    libjsoncpp25 \
    libpq5 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /app/build/cpp_microservice_template /app/cpp_microservice_template
COPY config/config.docker.json /app/config.json

EXPOSE 8080
CMD ["/app/cpp_microservice_template"]
