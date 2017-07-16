//
// Created by rick on 2017/7/16.
//

#include <memory>
#include <vector>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QFile>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include "VideoListModel.h"

using VideoData = QVector<QString>;
using VideoDataPtr = std::unique_ptr<VideoData>;

class VideoListModelPrivate {
public:
    VideoListModelPrivate() : _hasError(false) {
        int role = Qt::UserRole;
        _roleNames.insert(role++, "name");
        _roleNames.insert(role++, "date");
        _roleNames.insert(role++, "director_tag");
        _roleNames.insert(role++, "director");
        _roleNames.insert(role++, "actor_tag");
        _roleNames.insert(role++, "actor");
        _roleNames.insert(role++, "rating_tag");
        _roleNames.insert(role++, "rating");
        _roleNames.insert(role++, "desc_tag");
        _roleNames.insert(role++, "desc");
        _roleNames.insert(role++, "img");
        _roleNames.insert(role++, "playpage");
        _roleNames.insert(role++, "playtimes");
    }

    void load() {
        QXmlStreamReader reader;
        QFile file(_xmlFile);

        if (!file.exists()) {
            _hasError = true;
            _error = "File Not Found!";
            return;
        }

        if (!file.open(QFile::ReadOnly)) {
            _hasError = true;
            _error = file.errorString();
            return;
        }

        reader.setDevice(&file);
        mapXmlToVideoData(reader);
        file.close();

        if (reader.hasError()) {
            _hasError = true;
            _error = reader.errorString();
        }
    }

    void mapXmlToVideoData(QXmlStreamReader &reader) {
        QStringRef elementName;
        VideoDataPtr video;
        while (!reader.atEnd()) {
            reader.readNext();
            if (reader.isStartDocument()) {
                elementName = reader.name();
                if (elementName == "video") {
                    video = std::make_unique<VideoData>();
                    auto attrs = reader.attributes();
                    video->append(attrs.value("name").toString());
                    video->append(attrs.value("data").toString());
                } else if (elementName == "attr") {
                    video->append(reader.attributes().value("tag").toString());
                    video->append(reader.readElementText());
                } else if (elementName == "poster") {
                    video->append(reader.attributes().value("img").toString());
                } else if (elementName == "page") {
                    video->append(reader.attributes().value("link").toString());
                } else if (elementName == "playtimes") {
                    video->append(reader.readElementText());
                }
            } else if (reader.isEndElement()) {
                elementName = reader.name();
                if (elementName == "video") {
                    _videos.push_back(std::move(video));
                    video = 0;
                }
            }
        }
    }

    void reset() {
        _hasError = false;
        _error.clear();
        clear();
    }

    void clear() {
        int count = _videos.size();
        if (count > 0) {
            _videos.clear();
        }
    }

    QString _xmlFile;
    QString _error;
    bool _hasError;
    QHash<int, QByteArray> _roleNames;
    std::vector<VideoDataPtr> _videos;
};

int VideoListModel::rowCount(const QModelIndex &parent) const {
    return _dptr->_videos.size();
}

QVariant VideoListModel::data(const QModelIndex &index, int role) const {
    VideoDataPtr &d = _dptr->_videos[index.row()];
    if (role == Qt::DisplayRole)
        return d->at(0);
    else
        return d->at(role - Qt::UserRole);
}

QHash<int, QByteArray> VideoListModel::roleNames() const {
    return _dptr->_roleNames;
}

VideoListModel::VideoListModel(QObject *parent) : QAbstractListModel(parent), _dptr{new VideoListModelPrivate} {
}

QString VideoListModel::source() const {
    return _dptr->_xmlFile;
}

void VideoListModel::setSource(const QString &source) {
    _dptr->_xmlFile = source;
    reload();
    if (_dptr->_hasError) {
        qDebug() << "VideoListModel, error - " << _dptr->_error;
    }
}

QString VideoListModel::errorString() const {
    return _dptr->_error;
}

bool VideoListModel::hasError() const {
    return _dptr->_hasError;
}

void VideoListModel::reload() {
    beginResetModel();
    _dptr->reset();
    _dptr->load();
    endResetModel();
}

void VideoListModel::remove(int index) {
    beginRemoveRows(QModelIndex(), index, index);
    auto begin = _dptr->_videos.cbegin();
    _dptr->_videos.erase(begin + index);
    endRemoveRows();
}

VideoListModel::~VideoListModel() {

}
