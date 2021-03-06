﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include "bar.h"
#include "thr_play.h"
#include "thr_data.h"
#include "update_data.h"
#include "record_format.h"
#include "util.h"
#include "downloader.h"

#define PLAY_STATE_UNKNOWN      0
#define PLAY_STATE_RUNNING      1
#define PLAY_STATE_PAUSE        2
#define PLAY_STATE_STOP         3

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void set_resource(const QString& res);

    void pause();
    void resume(bool relocate, uint32_t ms);
    void restart();
    void set_speed(int s);
    void set_skip(bool s);

    // TODO: 将thr_data移动到thr_play线程，由play线程进行管理
    ThrData* get_thr_data() {return m_thr_data;}

private:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void _do_first_run(); // 默认界面加载完成后，开始播放操作（可能会进行数据下载）
    void _do_update_data(UpdateData*);
    void _do_bar_fade();
    void _do_bar_delay_hide();

private:
    Ui::MainWindow *ui;

    bool m_show_default;
    bool m_bar_shown;
    QPixmap m_default_bg;

    QString m_res;
    ThrPlay* m_thr_play;
    ThrData* m_thr_data;

    QPixmap m_canvas;

    Bar m_bar;

    TS_RECORD_HEADER m_rec_hdr;

    QPixmap m_pt_normal;
    TS_RECORD_RDP_POINTER m_pt;

    QTimer m_timer_first_run;
    QTimer m_timer_bar_fade;
    QTimer m_timer_bar_delay_hide;
    bool m_bar_fade_in;
    bool m_bar_fading;
    qreal m_bar_opacity;

    int m_play_state;

    bool m_show_message;
    QPixmap m_img_message;
    QRect m_rc_message;
    bool m_disable_draw;
};

#endif // MAINWINDOW_H
