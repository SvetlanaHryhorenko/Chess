#pragma once
#include <memory>
#include <QAbstractListModel>

class Logic: public QAbstractListModel
{
    Q_OBJECT
public:

    enum GlobalConstants {
        BOARD_SIZE = 8
    };

    enum Roles {
        Type = Qt::UserRole,
        PositionX,
        PositionY,
    };
    
public:
    explicit Logic(QObject *parent = 0);
    ~Logic();


    Q_PROPERTY(int boardSize READ boardSize CONSTANT)
    int boardSize() const;

    bool startButton=true;
    bool loadButton=true;
    bool stopButton;
    bool saveButton;
    bool prevButton;
    bool nextButton;
    bool continueButton;
    bool mouse;
    bool game_overText;

    Q_PROPERTY(bool startButton READ get_startButton WRITE set_startButton NOTIFY startButton_changed)
    Q_PROPERTY(bool loadButton READ get_loadButton WRITE set_loadButton NOTIFY loadButton_changed)
    Q_PROPERTY(bool stopButton READ get_stopButton WRITE set_stopButton NOTIFY stopButton_changed)
    Q_PROPERTY(bool saveButton READ get_saveButton WRITE set_saveButton NOTIFY saveButton_changed)
    Q_PROPERTY(bool prevButton READ get_prevButton WRITE set_prevButton NOTIFY prevButton_changed)
    Q_PROPERTY(bool nextButton READ get_nextButton WRITE set_nextButton NOTIFY nextButton_changed)
    Q_PROPERTY(bool continueButton READ get_continueButton WRITE set_continueButton NOTIFY continueButton_changed)
    Q_PROPERTY(bool mouse READ get_mouse WRITE set_mouse NOTIFY mouse_changed)
    Q_PROPERTY(bool game_overText READ get_game_over WRITE set_game_over NOTIFY game_over_changed)
    bool get_startButton() const;
    void set_startButton(const bool &);
    bool get_loadButton() const;
    void set_loadButton(const bool &);
    bool get_stopButton() const;
    void set_stopButton(const bool &);
    bool get_saveButton() const;
    void set_saveButton(const bool &);
    bool get_prevButton() const;
    void set_prevButton(const bool &);
    bool get_nextButton() const;
    void set_nextButton(const bool &);
    bool get_continueButton() const;
    void set_continueButton(const bool &);
    bool get_mouse() const;
    void set_mouse(const bool &);
    bool get_game_over() const;
    void set_game_over(const bool &);


    Q_INVOKABLE void start();
    Q_INVOKABLE void load();
    Q_INVOKABLE void stop();
    void clear();
    void game_over();
    Q_INVOKABLE void save();
    Q_INVOKABLE void prev();
    Q_INVOKABLE bool next();
    Q_INVOKABLE void cont();
    Q_INVOKABLE void del(int row/*,int count, const QModelIndex &parent/* = QModelIndex()*/);
    Q_INVOKABLE bool move(int fromX, int fromY, int toX, int toY);
    Q_INVOKABLE bool changePosition(int fromX, int fromY, int toX, int toY);


protected:
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:

    struct Impl;
    std::unique_ptr<Impl> impl;
signals:
     void startButton_changed();
     void loadButton_changed();
     void stopButton_changed();
     void saveButton_changed();
     void prevButton_changed();
     void nextButton_changed();
     void continueButton_changed();
     void mouse_changed();
     void game_over_changed();
};
