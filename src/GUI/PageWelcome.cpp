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

#include "PageWelcome.h"

#include "CommandLineOptions.h"
#include "Icons.h"
#include "MainWindow.h"

PageWelcome::PageWelcome(MainWindow* main_window)
	: QWidget(main_window->centralWidget()) {

	m_main_window = main_window;

	QScrollArea *scrollarea = new QScrollArea(this);
	QWidget *scrollarea_contents = new QWidget(scrollarea);
	scrollarea->setWidgetResizable(true);
	scrollarea->setWidget(scrollarea_contents);
	scrollarea->setFrameShape(QFrame::NoFrame);
	{
		QLabel *label_logo = new QLabel(scrollarea_contents);
		label_logo->setPixmap(QPixmap(":/header.png"));
		label_logo->setScaledContents(true);
		QLabel *label_text = new QLabel(scrollarea_contents);
		label_text->setText(tr("<p><b>bens_ssr</b> — Lighter fork of SimpleScreenRecorder</p>"
							   "<p>X11 + PulseAudio capture with FFmpeg encoding, stripped of hotkeys, scheduler, systray, "
							   "NVIDIA code and OpenGL recording.</p>"
							   "<p><i>Original code by Maarten Baert</i></p>"));
		label_text->setWordWrap(true);
		label_text->setAlignment(Qt::AlignCenter);

		QVBoxLayout *layout = new QVBoxLayout(scrollarea_contents);
		{
			QHBoxLayout *layout2 = new QHBoxLayout();
			layout->addLayout(layout2);
			layout2->addStretch();
			layout2->addWidget(label_logo);
			layout2->addStretch();
		}
		layout->addWidget(label_text);
		layout->addStretch();
	}
	QPushButton *button_continue = new QPushButton(g_icon_go_next, tr("Continue"), this);

	connect(button_continue, SIGNAL(clicked()), m_main_window, SLOT(GoPageInput()));

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(scrollarea);
	{
		QHBoxLayout *layout2 = new QHBoxLayout();
		layout->addLayout(layout2);
		layout2->addSpacing(style()->pixelMetric(QStyle::PM_LayoutLeftMargin));
		layout2->addWidget(button_continue);
		layout2->addSpacing(style()->pixelMetric(QStyle::PM_LayoutRightMargin));
	}
	layout->addSpacing(style()->pixelMetric(QStyle::PM_LayoutBottomMargin));

}





