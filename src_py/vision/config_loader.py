import yaml
import os


def load_config():
    # 假设 config.yaml 在项目根目录下
    config_path = os.path.join(os.path.dirname(__file__), "..", "config.yaml")
    with open(config_path, "r") as file:
        config = yaml.safe_load(file)
    return config


CONFIG = load_config()
