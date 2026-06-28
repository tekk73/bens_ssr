/*
Copyright (c) 2012-2020 Maarten Baert <maarten-baert@hotmail.com>

This file is part of SimpleScreenRecorder.

SimpleScreenRecorder is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SimpleScreenRecorder is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SimpleScreenRecorder.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "Global.h"

#include "Logger.h"
#include "PageInput.h"
#include "OutputSettings.h"
#include "OutputManager.h"
#include "ElidedLabel.h"


class MainWindow;

class Muxer;
class VideoEncoder;
class AudioEncoder;
class Synchronizer;
class X11Input;
#if SSR_USE_OPENGL_RECORDING
class GLInjectLauncher;
class GLInjectInput;
#endif
#if SSR_USE_V4L2
class V4L2Input;
#endif
#if SSR_USE_PIPEWIRE
class PipeWireInput;
#endif
#if SSR_USE_ALSA
class ALSAInput;
#endif
#if SSR_USE_PULSEAUDIO
class PulseAudioInput;
#endif
#if SSR_USE_JACK
class JACKInput;
#endif
class VideoPreviewer;
class AudioPreviewer;

class PageRecord : public QWidget {
	Q_OBJECT

private:
	static constexpr int PRIORITY_RECORD = 0, PRIORITY_PREVIEW = -1;

private:
	MainWindow *m_main_window;

	bool m_page_started, m_input_started, m_output_started, m_previewing;
	bool m_recorded_something, m_wait_saving, m_error_occurred;

	PageInput::enum_video_backend m_video_backend;
	PageInput::enum_video_x11_area m_video_x11_area;
#if SSR_USE_V4L2
	QString m_v4l2_device;
#endif
#if SSR_USE_PIPEWIRE
	QString m_pipewire_source;
#endif
	unsigned int m_video_x, m_video_y, m_video_in_width, m_video_in_height;
	unsigned int m_video_frame_rate;
	bool m_video_scaling;
	unsigned int m_video_scaled_width, m_video_scaled_height;
	bool m_video_record_cursor;
	bool m_audio_enabled;
	unsigned int m_audio_channels, m_audio_sample_rate;
	PageInput::enum_audio_backend m_audio_backend;
#if SSR_USE_ALSA
	QString m_alsa_source;
#endif
#if SSR_USE_PULSEAUDIO
	QString m_pulseaudio_source;
#endif

	OutputSettings m_output_settings;
	std::unique_ptr<OutputManager> m_output_manager;

	QString m_file_base;
	QString m_file_protocol;
	bool m_separate_files, m_add_timestamp;

	std::unique_ptr<X11Input> m_x11_input;
#if SSR_USE_OPENGL_RECORDING
	std::unique_ptr<GLInjectInput> m_gl_inject_input;
#endif
#if SSR_USE_V4L2
	std::unique_ptr<V4L2Input> m_v4l2_input;
#endif
#if SSR_USE_PIPEWIRE
	std::unique_ptr<PipeWireInput> m_pipewire_input;
#endif
#if SSR_USE_ALSA
	std::unique_ptr<ALSAInput> m_alsa_input;
#endif
#if SSR_USE_PULSEAUDIO
	std::unique_ptr<PulseAudioInput> m_pulseaudio_input;
#endif
#if SSR_USE_JACK
	std::unique_ptr<JACKInput> m_jack_input;
#endif

	QPushButton *m_pushbutton_record;

	QLabel *m_label_info_total_time, *m_label_info_frame_rate_in, *m_label_info_frame_rate_out, *m_label_info_size_in, *m_label_info_size_out;
	ElidedLabel *m_label_info_file_name;
	QLabel *m_label_info_file_size, *m_label_info_bit_rate;
	QCheckBox *m_checkbox_show_recording_area;

	QStackedLayout *m_stacked_layout_preview;
	QWidget *m_preview_page1, *m_preview_page2;
	QSpinBox *m_spinbox_preview_frame_rate;
	VideoPreviewer *m_video_previewer;
	QLabel *m_label_mic_icon;
	AudioPreviewer *m_audio_previewer;
	QPushButton *m_pushbutton_preview_start_stop;

	QTextEdit *m_textedit_log;

	QTimer *m_timer_update_info;

	std::unique_ptr<RecordingFrameWindow> m_recording_frame;

public:
	PageRecord(MainWindow* main_window);
	~PageRecord();

	// Called when the user tries to close the program. If this function returns true, the command will be blocked.
	// This is used to display a warning if the user is about to close the program during a recording.
	bool ShouldBlockClose();

	void LoadSettings(QSettings* settings);
	void SaveSettings(QSettings* settings);

	bool TryStartPage();
	void StartPage();
	void StopPage(bool save);
	void StartOutput();
	void StopOutput(bool final);
	void StartInput();
	void StopInput();

private:
	void FinishOutput();
	void UpdateInput();
	void UpdateRecordButton();
	void UpdatePreview();

public:
	inline bool GetShowRecordingArea() { return m_checkbox_show_recording_area->isChecked(); }
	inline unsigned int GetPreviewFrameRate() { return m_spinbox_preview_frame_rate->value(); }

	inline void SetShowRecordingArea(bool enable) { m_checkbox_show_recording_area->setChecked(enable); }
	inline void SetPreviewFrameRate(unsigned int frame_rate) { m_spinbox_preview_frame_rate->setValue(frame_rate); }

public slots:
	void OnUpdateRecordingFrame();

public slots:
	void OnRecordStart();
	void OnRecordPause();
	void OnRecordStartPause();
	void OnRecordCancel(bool confirm = true);
	void OnRecordSave(bool confirm = true);
	void OnPreviewStartStop();

private slots:
	void OnUpdateInformation();
	void OnNewLogLine(Logger::enum_type type, QString string);

};
