// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#ifndef PANDORA_DATA_TYPE_H
#define PANDORA_DATA_TYPE_H

#if defined(_WIN32)
#include <cpp/H5Cpp.h>
#else
#include <H5Cpp.h>
#endif

namespace pandora {

enum class DataType {
    Bool,
    Float,
    Double,
    Int8,
    Int16,
    Int32,
    Int64,
    UInt8,
    UInt16,
    UInt32,
    UInt64,
    Date,
    DateTime
};


H5::DataType data_type_to_h5_filetype(DataType dtype);


H5::DataType data_type_to_h5_memtype(DataType dtype);


size_t data_type_to_size(DataType dtype);

}

#endif //PANDORA_DATA_TYPE_H
