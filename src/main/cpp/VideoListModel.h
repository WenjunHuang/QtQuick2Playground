//
// Created by rick on 2017/7/16.
//

#ifndef QTQUICKPLAYGROUND_VIDEOLISTMODEL_H
#define QTQUICKPLAYGROUND_VIDEOLISTMODEL_H


#include <memory>
#include <QtCore/QAbstractListModel>

class VideoListModelPrivate;

class VideoListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QString source
               READ source
               WRITE setSource)
public:
    VideoListModel(QObject *parent = nullptr);
    ~VideoListModel();

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    QString source() const;

    void setSource(const QString &source);

    Q_INVOKABLE QString errorString() const;

    Q_INVOKABLE bool hasError() const;

    Q_INVOKABLE void reload();

    Q_INVOKABLE void remove(int index);

private:
    using VideoListModelPrivatePtr = std::unique_ptr<VideoListModelPrivate>;
    VideoListModelPrivatePtr _dptr;

};


#endif //QTQUICKPLAYGROUND_VIDEOLISTMODEL_H
