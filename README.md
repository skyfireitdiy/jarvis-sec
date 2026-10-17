# jarvis-sec

Jarvis 安全扫描工具：面向 C/C++/Rust 代码仓的安全审计 CLI。

`jarvis-sec`（别名 `jsec`）是 [Jarvis](https://github.com/skyfireitdiy/Jarvis) 生态中的独立安全扫描工具，从主仓库拆分而来。它直接以 `jarvis-ai-assistant` 作为运行时依赖，复用其 `PrettyOutput` / `Agent` / `ToolRegistry` 等基础设施。

## 安装

```bash
pip install jarvis-sec
```

> 依赖 `jarvis-ai-assistant>=7.0.1`，安装时会自动带上。

## 使用

```bash
# 查看帮助
jarvis-sec --help
jsec --help

# 配置安全扫描
jarvis-sec config

# 执行安全扫描（启发式 + 单Agent验证）
jarvis-sec scan --path ./target_project

# 从 JSON 分析安全问题
jarvis-sec analyze --input issues.json

# 仅启发式直扫
jarvis-sec heuristic --path ./target_project
```

配置文件路径为相对当前工作目录的 `.jarvis/sec/config.json`。

## 能力

- **启发式扫描**：基于正则与规则模板快速定位候选问题（C/C++/Rust）
- **污点传播分析**：追踪数据从 source 到 sink 的传播路径
- **调用图分析**：跨函数/跨文件分析
- **单 Agent 验证**：对候选问题逐条交由 Agent 验证，降低误报
- **Joern（可选）**：若系统安装了 [Joern](https://joern.io/)，自动启用更精确的代码属性图分析；未安装时自动降级为内置分析器

## 开发

```bash
pip install -e ".[dev]"
pytest tests/ -m "not slow"
ruff check src/
```

## 编排

`orchestration/jsec_adversarial.yaml` 是对抗式自进化编排配置：`jsec_adversary` 主动搜索漏洞并驱动 `jsec_rule_developer` 改进检测规则。

## License

MIT
