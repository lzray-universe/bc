# bc Web Build Template

本模板包含 GitHub Actions 配置，用于自动将 C++ 程序与 `answer.all` 数据打包为 WebAssembly 并部署到 GitHub Pages。

## 使用方式

1. 在你的 `bc` 仓库根目录执行：
    ```bash
    tar -zxvf bc_web_package.tar.gz -C .
    ```
2. 提交并推送：
    ```bash
    git add .
    git commit -m "Add WebAssembly build & deploy CI and source files"
    git push
    ```
3. 确保在 GitHub 仓库设置中，Pages 来源为 `main` 分支的 `/docs` 文件夹。

完成后，每次推送到 `main` 分支时，CI 会自动构建并部署你的 C++ 猜数字游戏到 GitHub Pages。
