# PrettyLlama (WIP)

<p align="center">
  <img src="https://github.com/thenry42/PrettyLlama/blob/main/utils/PrettyLlama.png" alt="Project Logo" width="300" height="300">
</p>

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## Introduction

### Ollama x Glow

<p align="center">
  <img src="https://camo.githubusercontent.com/e20892cc1a5b1775de4ba67dd0baad0fc62191da6b71efff35b71f89800c1da2/68747470733a2f2f73747566662e636861726d2e73682f676c6f772f676c6f772d62616e6e65722d6769746875622e676966" width="750" height="200">
</p>

PrettyLlama is a Simple CLI tool that allows to run ollama models and render their answers in Markdown.

## Features
Keep in mind that this project is only available on Linux and is still a work in progress.

You will be able to: 
- Run a single model or multiple models at the same time with a single prompt.
- Ask a model to synthesize the answers of other models, using the "Super-model" feature (WIP).

Answers will always be rendered using Glow, for better readability.

## Installation

### Prerequisites
First, you need to install [Ollama](https://github.com/ollama/ollama), and download the models you are interested in.

Secondly, you need to install [Glow](https://github.com/charmbracelet/glow).

### Get PrettyLlama
Clone this repository:
```bash
git clone https://github.com/thenry42/PrettyLlama.git
```

Then Make:
```bash
make
```

If everything works fine and the binary file has been properly created, you may install the program by running the following commands:
```bash
sudo chmod +x install.sh
sudo ./install.sh
```

Note: you can undo this by using the uninstall.sh script.
```bash
sudo chmod +x uninstall.sh
sudo ./uninstall.sh
```

## Usage

### Launch the program in a Terminal

Once the installation is complete, you can simply launch the program by running the following command in your terminal:
```bash
PrettyLlama
```

### Launch using the application (desktop file)

Assuming the installation went well, you can launch the program by clicking on its icon in the App panel. It should open a new window.

You can also pin the app to your Dashboard for quick access.

Note that the desktop file use ```gnome-terminal``` to open a new terminal.

### How it works ?

