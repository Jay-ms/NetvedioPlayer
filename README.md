# NetvedioPlayer

## 开发环境
- **运行平台**：Qt Creator 4.12.2  
- **构建套件**：Qt 5.12.9（MinGW 64bit）  
- **音视频编解码库**：FFmpeg（[下载地址](https://github.com/BtbN/FFmpeg-Builds/releases)，版本：ffmpeg-master-latest-win64-gpl-shared.zip）

## 项目简介
NetvedioPlayer 是一个基于 Qt 的网络视频流播放器，作为 NetvedioAgent（具备 AI 识别功能的网络监控摄像头）前端工程。界面如下：

<img width="982" height="632" alt="3717f0ed31b467a1363c983d151f1a21" src="https://github.com/user-attachments/assets/fc778275-dfe9-44da-b9cd-d574423d0506" />

## 架构设计

### 整体架构
本项目采用标准 **MVC（Model-View-Controller）架构模式**，实现业务逻辑、数据处理与用户界面的完全解耦，便于后期维护、功能扩展与代码复用。

### 核心模块

#### 📊 Model（数据模型层）
负责核心业务逻辑与数据处理：
- **FFmpeg 视频处理模块**：支持多路视频流（最大4路）的并发拉取、解码与格式转换
  - 支持 RTSP 网络视频流接入
  - 实时解码 H.264 视频流
  - 多线程处理，确保播放流畅性
- **TCP 服务器模块**：监听端口，处理客户端连接与控制指令
  - 管理多客户端连接映射
  - 接收并转发云台控制信号
  - 支持设备状态同步

#### 🎨 View（视图展示层）
采用模块化 UI 设计，包含四个核心子视图：
- **UrlView**：RTSP 地址输入与管理界面
- **VedioView**：2×2 网格布局的多路视频显示区域，支持最大4路视频同时显示（可根据自行需求更改最大支持路数）
- **ControlbtnView**：集成云台控制与系统模式切换
  - 云台方向控制（上/下/左/右/复位）
  - 工作模式切换（自动/手动）
  - 视频播放控制（开始/停止）
- **InfoView**：实时显示当前连接的客户端信息

#### 🎯 Controller（控制器层）
作为 Model 与 View 的中介，负责：
- 初始化并配置 Model 与 View 的关联关系
- 处理用户交互事件并转发给相应的 Model 处理
- 管理信号与槽函数的连接，实现组件间的松耦合通信
- 协调多路视频流的播放状态管理
