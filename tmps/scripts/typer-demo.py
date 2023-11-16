# Example using Typer for a simple command-line application

import typer
from pathlib import Path

app = typer.Typer()

@app.command()
def get_model(
    model_manifest: Path = typer.Argument(..., exists=True, help="模型清单文件"),
    save_path: Path = typer.Option("model", "-o", help="模型保存路径"),
    update: bool = typer.Option(False, "-u", help="强制更新"),
    devcenter_user: str = typer.Option(
        "model_download_robot", "-du", help="devcenter username"
    ),
    devcenter_secret: str = typer.Option(
        "downloader",
        "-dp",
        help="devcenter password",
        show_default=False,
    ),
    adela_user: str = typer.Option("kestrel-robot", "-au", help="adela username"),
    adela_secret: str = typer.Option(
        "602bcdab78074fe0bbffd33262b6d917",
        "-ap",
        help="adela password",
        show_default=False,
    ),
    shape: list = typer.Option([224, 224, 3], "-s", help="模型输入尺寸")
):
  print(f"model_manifest: {model_manifest}")
  print(f"save_path: {save_path}")
  print(f"update: {update}")
  print(f"devcenter_user: {devcenter_user}")
  print(f"devcenter_secret: {devcenter_secret}")
  print(f"adela_user: {adela_user}")
  print(f"adela_secret: {adela_secret}")

if __name__ == "__main__":
  app()
