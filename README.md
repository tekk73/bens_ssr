SSR — Fork of SimpleScreenRecorder
===================================

This is a personal fork of [SimpleScreenRecorder](https://www.maartenbaert.be/simplescreenrecorder/)
by [Maarten Baert](https://github.com/MaartenBaert/ssr). All credit for the original
program goes to him.

### What's different

This fork strips out the following features from upstream SSR:

- Scheduler / timed recording
- Hotkeys (XInput2 dependency dropped)
- System tray icon
- Sound notifications (ALSA synth beeps)
- Benchmark mode
- NVIDIA driver flipping
- Cursor-follow / follow-fullscreen (GUI options removed — engine still captures full screen or fixed area)
- SyncDiagram (Synchronizer debug visualization)
- Translations (`.ts` / `.qm` files and infrastructure)
- OpenGL recording / GLInject (fully removed, including the GLInject library, shared-memory stream protocol, `DialogGLInject`, and `GLInjectInput`)
- ALSA, JACK, PipeWire, V4L2 backends (fully removed — only PulseAudio remains)
- Maarten's welcome text (replaced with just the logo)
- Dark theme applied program-wide

### What's kept

- **X11 screen capture** (with cursor, fixed-area recording)
- **PulseAudio audio capture**
- **Synchronizer** with full drift-correction
- **FFmpeg encoding and muxing** (video + audio)
- **FastScaler, FastResampler**
- **Multiple containers & codecs**
- **Preview window**

### Building

```bash
mkdir build && cd build
cmake -DWITH_QT5=TRUE -DWITH_PULSEAUDIO=TRUE \
      -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

Dependencies: `gcc`, `cmake`, `pkg-config`, `qtbase5-dev`, `libqt5x11extras5-dev`,
`libavformat-dev`, `libavcodec-dev`, `libavutil-dev`, `libswscale-dev`,
`libpulse-dev`, `libx11-dev`, `libxext-dev`, `libxfixes-dev`, `libxi-dev`,
`libxinerama-dev`.

### License

GNU GPL v3 — see `COPYING`.
