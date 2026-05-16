# Repository Guidelines

## Project Structure & Module Organization
- `src/main.cpp`: service entrypoint, loads Drogon config and starts the app.
- `src/controllers/`: HTTP layer (`HealthController`, `UserController`) and route-facing logic.
- `src/services/`: business rules and orchestration (`UserService`).
- `src/repositories/`: database access via Drogon ORM (`UserRepository`).
- `src/domain/`: domain models/DTOs.
- `config/config.json`: local runtime config.
- `config/config.docker.json`: Docker runtime config (uses `db` host).
- `migrations/`: SQL schema setup scripts (for example `001_create_users.sql`).
- `Dockerfile`, `docker-compose.yml`: containerized build and runtime.

## Build, Test, and Development Commands
- `cmake -S . -B build`: configure CMake build files.
- `cmake --build build -j`: compile the service binary.
- `./start.sh`: local build + run helper (copies config and starts app).
- `docker compose up --build`: build and run app + PostgreSQL.
- `docker compose down -v`: stop services and remove DB volume for clean re-init.
- `docker compose config`: validate Compose syntax.

## Coding Style & Naming Conventions
- Language: C++20.
- Indentation: 2 spaces, no tabs.
- Types/classes: `PascalCase` (e.g., `UserService`).
- Methods/variables: `camelCase`.
- Filenames: `PascalCase.cpp/.h` aligned to class names.
- Keep controllers thin, move business logic to services, and SQL/data concerns to repositories.

## Testing Guidelines
- No automated test suite is currently committed.
- Validate changes with:
  - `docker compose up --build`
  - `curl http://localhost:8080/health`
  - endpoint smoke tests for create/get/list/delete user flows.
- When adding tests, place them in a dedicated `tests/` directory and mirror module names.

## Commit & Pull Request Guidelines
- Prefer concise, imperative commit messages: `Add Dockerized app startup`, `Fix DB connection config`.
- Keep commits focused (one logical change per commit).
- PRs should include:
  - what changed and why,
  - how to run/verify locally,
  - config or migration impacts,
  - sample API calls/responses when behavior changes.

## Security & Configuration Tips
- Do not commit secrets; use env vars or local overrides for credentials.
- Treat `config/*.json` as environment-specific templates and keep production credentials external.
