#ifndef UPDATEREXCEPTION_H
#define UPDATEREXCEPTION_H

#include <stdexcept>
#include <QString>

//===========================================================================//

class UpdaterException : public std::runtime_error
{
public:
    explicit UpdaterException(const QString what) : std::runtime_error(what.toStdString()) {}
    QString description() const { return QString::fromStdString(std::runtime_error::what()); }
};

//===========================================================================//

class InvalidArgException : public UpdaterException
{
public:
    explicit InvalidArgException(const QString what) : UpdaterException(what) {}
};

//===========================================================================//

class InvalidSchemeException : public InvalidArgException
{
public:
    explicit InvalidSchemeException(const QString what) : InvalidArgException(what) {}
};

//===========================================================================//

#endif // UPDATEREXCEPTION_H
