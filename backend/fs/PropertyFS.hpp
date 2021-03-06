// Copyright (c) 2013 - 2015, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#ifndef NIX_PROPERTY_FS_H
#define NIX_PROPERTY_FS_H

#include <nix/base/IFile.hpp>
#include <nix/base/IEntity.hpp>
#include <nix/base/IProperty.hpp>
#include <nix/DataType.hpp>
#include "DirectoryWithAttributes.hpp"

#include <string>
#include <memory>
#include <ctime>

namespace nix {
namespace file {


class PropertyFS : virtual public base::IProperty, public DirectoryWithAttributes,
                   public std::enable_shared_from_this<PropertyFS> {

public:
    PropertyFS(const std::shared_ptr<base::IFile> &file, const boost::filesystem::path &loc);


    PropertyFS(const std::shared_ptr<base::IFile> &file, const boost::filesystem::path &loc, const std::string &id,
               const std::string &name, const DataType &dataType);


    std::string id() const;


    time_t updatedAt() const;


    time_t createdAt() const;


    void setUpdatedAt();


    void forceUpdatedAt();


    void setCreatedAt();


    void forceCreatedAt(time_t t);


    std::string name() const;


    boost::optional<std::string> definition() const;


    void definition(const std::string &definition);


    void definition(const none_t t);


    DataType dataType() const;


    void unit(const std::string &unit);


    boost::optional<std::string> unit() const;


    void unit(const none_t t);


    void uncertainty(double uncertainty);


    boost::optional<double> uncertainty() const;


    void uncertainty(const none_t t);


    void deleteValues();


    ndsize_t valueCount() const;


    void values(const std::vector<Variant> &values);


    std::vector<Variant> values(void) const;


    void values(const boost::none_t t);


    bool isValidEntity() const;


    int compare(const std::shared_ptr<IProperty> &other) const;


    bool operator==(const PropertyFS &other) const; //FIXME: not implemented


    bool operator!=(const PropertyFS &other) const; //FIXME: not implemented


    virtual ~PropertyFS();

};


} // namespace file
} // namespace nix

#endif // NIX_PROPERTY_FS_H
