SSR — Fork of SimpleScreenRecorder
===================================

This is a personal fork of [SimpleScreenRecorder](https://www.maartenbaert.be/simplescreenrecorder/)
by [Maarten Baert](https://github.com/MaartenBaert/ssr). All credit for the original
program goes to him.

### Why this fork exists

I wanted a lighter, simpler version of SSR for my own use. This fork strips out:

- **Scheduler / timed recording** — removed `DialogRecordSchedule`
- **Hotkeys** — removed `HotkeyListener` (XInput2 dependency dropped)
- **System tray icon** — no more `QSystemTrayIcon`
- **Sound notifications** — removed `SimpleSynth` (ALSA synth for record start/stop beeps)
- **Benchmark mode** — removed `Benchmark`
- **NVIDIA driver flipping** — removed NVidia control code
- **Cursor-follow / follow-fullscreen** — X11 area GUI options removed (engine still captures full screen or fixed area)
- **SyncDiagram** — debug visualization of Synchronizer drift removed
- **Translations** — all `.ts` files removed
- **OpenGL recording / GLInject** — disabled at build time
- **Non-PulseAudio backends** — ALSA, JACK, PipeWire disabled at build time
- **Maarten's welcome text** — replaced with just the logo
- **Dark theme** — applied program-wide for instant visual distinction

### What's kept intact

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
      -DWITH_ALSA=FALSE -DWITH_JACK=FALSE \
      -DWITH_OPENGL_RECORDING=FALSE -DWITH_GLINJECT=FALSE \
      -DWITH_V4L2=FALSE -DWITH_PIPEWIRE=FALSE \
      -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

Dependencies: `gcc`, `cmake`, `pkg-config`, `qtbase5-dev`, `libqt5x11extras5-dev`,
`libavformat-dev`, `libavcodec-dev`, `libavutil-dev`, `libswscale-dev`,
`libpulse-dev`, `libx11-dev`, `libxext-dev`, `libxfixes-dev`, `libxi-dev`,
`libxinerama-dev`.

### License

GNU GPL v3 — see `COPYING`.
