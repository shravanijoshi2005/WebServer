# Simple HTTP Web Server in C++

## 📌 Overview
This project is a basic HTTP web server written in **C++** using the **Winsock2 API**. It listens on **port 8080**, accepts incoming connections, processes simple HTTP GET requests, and responds with a basic "Hello, World!" message.

## 📂 Features
- Uses **Winsock2** for socket programming.
- Supports **basic HTTP request handling**.
- Sends a simple **HTML response**.
- Runs on **Windows**.

## 🛠️ Requirements
- Windows OS
- MinGW or MSVC compiler
- Winsock2 library (`ws2_32.lib`)

## 🚀 Installation & Setup

### **1️⃣ Compile the Server**
Run the following command in **cmd** to compile the program using MinGW:
```sh
g++ server.cpp -o server.exe -lws2_32

