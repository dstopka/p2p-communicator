//
// Created by student on 27.01.2020.
//

#include "include/File.hpp"

File::File(QString str, bool sent): url(std::move(str)), sender(sent)
{

};

QString File::getUrl()
{
    return url;
}

void File::setUrl(QString url)
{
    this->url = std::move(url);
}

bool File::isSender()
{
    return sender;
}
