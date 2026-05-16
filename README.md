# C++ Microservice Template (Drogon + PostgreSQL)

Reusable C++ microservice starter template with:
- HTTP API using Drogon
- PostgreSQL connection
- ORM-style repository/service/controller layers
- Ready migration SQL
- Fully Dockerized local runtime

## Stack
- C++20
- [Drogon](https://github.com/drogonframework/drogon)
- PostgreSQL
- CMake
- Docker Compose

## Project Structure

- `src/controllers`: HTTP endpoints
- `src/services`: business logic
- `src/repositories`: persistence layer using Drogon ORM client
- `src/domain`: DTO/domain objects
- `config/config.json`: runtime config for local host run
- `config/config.docker.json`: runtime config for Docker (`db` hostname)
- `migrations`: SQL schema migrations
- `Dockerfile`: app build/runtime image
- `docker-compose.yml`: app + db orchestration

## API Endpoints

- `GET /health`
- `POST /api/v1/users`
- `GET /api/v1/users/{id}`
- `GET /api/v1/users`
- `DELETE /api/v1/users/{id}`

## Quick Start (Docker, Recommended)

Start everything (DB + migration + app):

```bash
docker compose up --build
```

Run in background:

```bash
docker compose up --build -d
```

Stop:

```bash
docker compose down
```

App URL: `http://localhost:8080`

Note: Migration SQL is mounted into `/docker-entrypoint-initdb.d` and is applied automatically when the Postgres data volume is initialized.

If you need to re-apply init scripts from scratch:

```bash
docker compose down -v
docker compose up --build
```

## Optional: Local Host Build (No Docker for app)

If you want to run app directly on host:

```bash
cmake -S . -B build
cmake --build build -j
cp config/config.json build/config.json
./build/cpp_microservice_template
```

## Example Requests

Create user:

```bash
curl -X POST http://localhost:8080/api/v1/users \
  -H "content-type: application/json" \
  -d '{"name":"Ada Lovelace","email":"ada@example.com"}'
```

Get all users:

```bash
curl http://localhost:8080/api/v1/users
```
# c-micro-service
# c-micro-service
