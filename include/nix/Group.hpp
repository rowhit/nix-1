// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#ifndef NIX_GROUP_HPP
#define NIX_GROUP_HPP

#include <nix/base/EntityWithSources.hpp>
#include <nix/base/IGroup.hpp>
#include <nix/DataArray.hpp>
#include <nix/DataFrame.hpp>
#include <nix/Platform.hpp>
#include <nix/ObjectType.hpp>
#include <nix/util/util.hpp>


namespace nix {

class NIXAPI Group : public base::EntityWithSources<base::IGroup> {

public:

    /**
     * @brief Constructor that creates an uninitialized Group.
     *
     * Calling any method on an uninitialized group will throw a {@link nix::UninitializedEntity}
     * exception. The following code illustrates how to check if a group is initialized:
     *
     * ~~~
     * Group g = ...;
     * if (g) {
     *     // g is initialised
     * } else {
     *     // g is uninitialized
     * }
     * ~~~
     */
    Group()
        : EntityWithSources() { }

    /**
     * @brief Copy constructor.
     *
     * Copying of all NIX front facing objects like Group is a rather cheap operation.
     * Semantically this is equivalent to the creation of another reference to the original
     * object.
     *
     * @param other     The group to copy.
     */
    Group(const Group &other)
        : EntityWithSources(other.impl()) {
    }

    /**
     * @brief Constructor that creates a new group from a shared pointer to
     * an implementation instance.
     *
     * This constructor should only be used in the back-end.
     */
    Group(const std::shared_ptr<base::IGroup> &p_impl)
        : EntityWithSources(p_impl) {
    }

    /**
     * @brief Constructor with move semantics that creates a new group from a shared pointer to
     * an implementation instance.
     *
     * This constructor should only be used in the back-end.
     */
    Group(std::shared_ptr<base::IGroup> &&ptr)
        : EntityWithSources(std::move(ptr)) {
    }

    //--------------------------------------------------
    // Methods concerning data arrays.
    //--------------------------------------------------
    // TODO syntactic sugar for creating dataArrays, tags, multiTags
    /**
     * @brief Checks whether a DataArray is referenced by the group.
     *
     * @param id        The id of the DataArray to check.
     *
     * @return True if the data array is referenced, false otherwise.
     */
    bool hasDataArray(const std::string &name_or_id) const {
        return backend()->hasEntity({name_or_id, ObjectType::DataArray});
    }

    /**
     * @brief Checks whether a DataArray is referenced by the group.
     *
     * @param data_array The DataArray to check.
     *
     * @return True if the data array is referenced, false otherwise.
     */
    bool hasDataArray(const DataArray &data_array) const {
        if (!util::checkEntityInput(data_array, false)) {
            return false;
        }
        return backend()->hasEntity(data_array);
    }

    /**
     * @brief Gets the number of referenced DataArray entities of the tag.
     *
     * @return The number of referenced data arrays.
     */
    ndsize_t dataArrayCount() const {
        return backend()->entityCount(ObjectType::DataArray);
    }

    /**
     * @brief Gets a specific referenced DataArray from the tag.
     *
     * @param name_or_id           The name or id of the referenced
     *                             DataArray (using the id is faster).
     *
     * @return The referenced data array.
     */
    DataArray getDataArray(const std::string &name_or_id) const {
        return backend()->getEntity<base::IDataArray>(name_or_id);
    }

    /**
     * @brief Gets a referenced DataArray by its index.
     *
     * @param index     The index of the DataArray.
     *
     * @return The referenced data array.
     */
    DataArray getDataArray(size_t index) const {
        if (index >= backend()->entityCount(ObjectType::DataArray)) {
            throw OutOfBounds("No DataArray at given index", index);
        }
        return backend()->getEntity<base::IDataArray>(index);
    }

    /**
     * @brief Add a DataArray to the list of referenced data of the group.
     *
     * @param data_array The DataArray to add.
     */
    void addDataArray(const DataArray &data_array) {
        if (util::checkEntityInput(data_array, true)) {
            backend()->addEntity(data_array);
        }
    }
    /**
     * @brief Add a DataArray to the list of referenced data of the group.
     *
     * @param name_or_id        The name or id of the DataArray to add.
     */
    void addDataArray(const std::string &name_or_id) {
        backend()->addEntity({name_or_id, ObjectType::DataArray});
    }
    /**
     * @brief Remove a DataArray from the list of referenced data of the group.
     *
     * This method just removes the association between the data array and the
     * tag, the data array itself will not be removed from the file.
     *
     * @param data_array The DataArray to remove.
     *
     * @returns True if the DataArray was removed, false otherwise.
     */
    bool removeDataArray(const DataArray &data_array) {
        if (!util::checkEntityInput(data_array, false)) {
            return false;
        }
        return backend()->removeEntity(data_array);
    }
    /**
     * @brief Remove a DataArray from the list of referenced data of the group.
     *
     * This method just removes the association between the data array and the
     * tag, the data array itself will not be removed from the file.
     *
     * @param name_or_id        The name or the id of the DataArray to
     *                          remove. (using the id is faster)
     *
     * @returns True if the DataArray was removed, false otherwise.
     */
    bool removeDataArray(const std::string &name_or_id) {
        return backend()->removeEntity({name_or_id, ObjectType::DataArray});
    }

    /**
     * @brief Get referenced data arrays associated with this group.
     *
     * The parameter filter can be used to filter data arrays by various
     * criteria.
     *
     * @param filter    A filter function.
     *
     * @return A vector containing the matching data arrays.
     */
    std::vector<DataArray> dataArrays(const util::Filter<DataArray>::type &filter) const;

    /**
     * @brief Get all referenced data arrays associated with this group.
     *
     * Always uses filter that accepts all dataArrays.
     *
     * @return The filtered DataArrays as a vector
     */
    std::vector<DataArray> dataArrays() const
    {
        return dataArrays(util::AcceptAll<DataArray>());
    }

    /**
     * @brief Sets all referenced DataArray entities.
     *
     * Previously referenced data arrays, that are not in the references vector
     * will be removed.
     *
     * @param data_arrays    All referenced arrays.
     */
    void dataArrays(const std::vector<DataArray> &data_arrays);

    //--------------------------------------------------
    // Methods concerning data frames.
    //--------------------------------------------------
    /**
     * @brief Checks whether a DataFrame is referenced by the group.
     *
     * @param id        The id of the DataFrame to check.
     *
     * @return True if the data frame is referenced, false otherwise.
     */
    bool hasDataFrame(const std::string &name_or_id) const {
        return backend()->hasEntity({name_or_id, ObjectType::DataFrame});
    }

    /**
     * @brief Checks whether a DataFrame is referenced by the group.
     *
     * @param data_frame The DataFrame to check.
     *
     * @return True if the data frame is referenced, false otherwise.
     */
    bool hasDataFrame(const DataFrame &data_frame) const {
        if (!util::checkEntityInput(data_frame, false)) {
            return false;
        }
        return backend()->hasEntity(data_frame);
    }

    /**
     * @brief Gets the number of referenced DataFrame entities of the tag.
     *
     * @return The number of referenced data frames.
     */
    ndsize_t dataFrameCount() const {
        return backend()->entityCount(ObjectType::DataFrame);
    }

    /**
     * @brief Gets a specific referenced DataFrame from the tag.
     *
     * @param name_or_id           The name or id of the referenced
     *                             DataFrame (using the id is faster).
     *
     * @return The referenced data frame.
     */
    DataFrame getDataFrame(const std::string &name_or_id) const {
        return backend()->getEntity<base::IDataFrame>(name_or_id);
    }

    /**
     * @brief Gets a referenced DataFrame by its index.
     *
     * @param index     The index of the DataFrame.
     *
     * @return The referenced data frame.
     */
    DataFrame getDataFrame(ndsize_t index) const {
        if (index >= backend()->entityCount(ObjectType::DataFrame)) {
            throw OutOfBounds("No DataFrame at given index", index);
        }
        return backend()->getEntity<base::IDataFrame>(index);
    }

    /**
     * @brief Add a DataFrame to the list of referenced data of the group.
     *
     * @param data_frame The DataFrame to add.
     */
    void addDataFrame(const DataFrame &data_frame) {
        if (util::checkEntityInput(data_frame, true)) {
            backend()->addEntity(data_frame);
        }
    }
    /**
     * @brief Add a DataFrame to the list of referenced data of the group.
     *
     * @param name_or_id        The name or id of the DataFrame to add.
     */
    void addDataFrame(const std::string &name_or_id) {
        backend()->addEntity({name_or_id, ObjectType::DataFrame});
    }
    /**
     * @brief Remove a DataFrame from the list of referenced data of the group.
     *
     * This method just removes the association between the data frame and the
     * tag, the data frame itself will not be removed from the file.
     *
     * @param data_frame The DataFrame to remove.
     *
     * @returns True if the DataFrame was removed, false otherwise.
     */
    bool removeDataFrame(const DataFrame &data_frame) {
        if (!util::checkEntityInput(data_frame, false)) {
            return false;
        }
        return backend()->removeEntity(data_frame);
    }
    /**
     * @brief Remove a DataFrame from the list of referenced data of the group.
     *
     * This method just removes the association between the data frame and the
     * tag, the data frame itself will not be removed from the file.
     *
     * @param name_or_id        The name or the id of the DataFrame to
     *                          remove. (using the id is faster)
     *
     * @returns True if the DataFrame was removed, false otherwise.
     */
    bool removeDataFrame(const std::string &name_or_id) {
        return backend()->removeEntity({name_or_id, ObjectType::DataFrame});
    }

    /**
     * @brief Get referenced data frames associated with this group.
     *
     * The parameter filter can be used to filter data frames by various
     * criteria.
     *
     * @param filter    A filter function.
     *
     * @return A vector containing the matching data frames.
     */
    std::vector<DataFrame> dataFrames(const util::Filter<DataFrame>::type &filter) const;

    /**
     * @brief Get all referenced data frames associated with this group.
     *
     * Always uses filter that accepts all dataFrames.
     *
     * @return The filtered DataFrames as a vector
     */
    std::vector<DataFrame> dataFrames() const
    {
        return dataFrames(util::AcceptAll<DataFrame>());
    }

    /**
     * @brief Sets all referenced DataFrame entities.
     *
     * Previously referenced data frames, that are not in the references vector
     * will be removed.
     *
     * @param data_frames    All referenced arrays.
     */
    void dataFrames(const std::vector<DataFrame> &data_frames);

    //--------------------------------------------------
    // Methods concerning tags.
    //--------------------------------------------------

    /**
     * @brief Checks whether a Tag is referenced by the group.
     *
     * @param name_or_id      The name or id of the Tag to check.
     *
     * @return True if the tag is referenced, false otherwise.
     */
    bool hasTag(const std::string &name_or_id) const {
        return backend()->hasEntity({name_or_id, ObjectType::Tag});
    }

    /**
     * @brief Checks whether a Tag is referenced by the group.
     *
     * @param tag      The Tagto check.
     *
     * @return True if the tag is referenced, false otherwise.
     */
    bool hasTag(const Tag &tag) const {
        if (!util::checkEntityInput(tag, false)) {
            return false;
        }
        return backend()->hasEntity(tag);
    }

    /**
     * @brief Gets the number of referenced Tag entities of the tag.
     *
     * @return The number of referenced tags.
     */
    ndsize_t tagCount() const {
        return backend()->entityCount(ObjectType::Tag);
    }

    /**
     * @brief Gets a specific referenced Tag from the tag.
     *
     * @param name_or_id      The name or id of the referenced Tag.
     *
     * @return The referenced tag.
     */
    Tag getTag(const std::string &name_or_id) const {
        return backend()->getEntity<base::ITag>(name_or_id);
    }

    /**
     * @brief Gets a referenced Tag by its index.
     *
     * @param index     The index of the Tag.
     *
     * @return The referenced tag.
     */
    Tag getTag(size_t index) const {
        if (index >= backend()->entityCount(ObjectType::Tag)) {
            throw OutOfBounds("No Tag at given index", index);
        }
        return backend()->getEntity<base::ITag>(index);
    }

    /**
     * @brief Add a Tag to the list of referenced data of the group.
     *
     * @param tag The Tag to add.
     */
    void addTag(const Tag &tag) {
        if (util::checkEntityInput(tag, true)) {
            backend()->addEntity(tag);
        }
    }

    /**
     * @brief Add a Tag to the list of referenced data of the group.
     *
     * @param name_or_id        The name or id of the Tag to add.
     */
    void addTag(const std::string &name_or_id) {
        backend()->addEntity({name_or_id, ObjectType::Tag});
    }

    /**
     * @brief Remove a Tag from the list of referenced tags of the group.
     *
     * This method just removes the association between the tag  and the
     * group, the tag itself will not be removed from the file.
     *
     * @param tag     The Tag to remove.
     *
     * @returns True if the Tag was removed, false otherwise.
     */
    bool removeTag(const Tag &tag) {
          if (!util::checkEntityInput(tag, false)) {
            return false;
        }
        return backend()->removeEntity(tag);
    }

    /**
     * @brief Remove a Tag from the list of referenced tags of the group.
     *
     * This method just removes the association between the tag and the
     * group, the tag itself will not be removed from the file.
     *
     * @param name_or_id        The name or id of the Tag to remove.
     *
     * @returns True if the Tag was removed, false otherwise.
     */
    bool removeTag(const std::string &name_or_id) {
        return backend()->removeEntity({name_or_id, ObjectType::Tag});
    }

    /**
     * @brief Get referenced tag associated with this group.
     *
     * The parameter filter can be used to filter tags by various
     * criteria.
     *
     * @param filter    A filter function.
     *
     * @return A vector containing the matching tags.
     */
    std::vector<Tag> tags(const util::Filter<Tag>::type &filter) const;

    /**
     * @brief Get all referenced tags associated with this group.
     *
     * Always uses filter that accepts all tags.
     *
     * @return The filtered Tags as a vector
     */
    std::vector<Tag> tags() const {
        return tags(util::AcceptAll<Tag>());
    }

    /**
     * @brief Sets all referenced Tag entities.
     *
     * Previously referenced tags, that are not in the passed vector
     * will be removed.
     *
     * @param tags    All tags.
     */
    void tags(const std::vector<Tag> &tags);
    //--------------------------------------------------
    // Methods concerning multi tags.
    //--------------------------------------------------

    /**
     * @brief Checks whether a MultiTag is referenced by the group.
     *
     * @param name or id        The name or id of the MultiTag to check.
     *
     * @return True if the MultiTag is referenced, false otherwise.
     */
    bool hasMultiTag(const std::string &name_or_id) const {
        return backend()->hasEntity({name_or_id, ObjectType::MultiTag});
    }

    /**
     * @brief Checks whether a MultiTag is referenced by the group.
     *
     * @param tag      The MultiTag to check.
     *
     * @return True if the MultiTag is referenced, false otherwise.
     */
    bool hasMultiTag(const MultiTag &tag) const {
        if (!util::checkEntityInput(tag, false)) {
            return false;
        }
        return backend()->hasEntity(tag);
    }


    /**
     * @brief Gets the number of referenced MultiTag entities of the group.
     *
     * @return The number of referenced MultiTags.
     */
    ndsize_t multiTagCount() const {
        return backend()->entityCount(ObjectType::MultiTag);
    }

    /**
     * @brief Gets a specific referenced MultiTag from the group.
     *
     * @param name_or_id        The name or id of the referenced MultiTag.
     *
     * @return The referenced MultiTag.
     */
    MultiTag getMultiTag(const std::string &name_or_id) const {
        return backend()->getEntity<base::IMultiTag>(name_or_id);
    }

    /**
     * @brief Gets a referenced MultiTag by its index.
     *
     * @param index     The index of the MultiTag.
     *
     * @return The referenced MultiTag.
     */
    MultiTag getMultiTag(size_t index) const {
        if (index >= backend()->entityCount(ObjectType::MultiTag)) {
            throw OutOfBounds("No MultiTag at given index", index);
        }
        return backend()->getEntity<base::IMultiTag>(index);
    }

    /**
     * @brief Add a MultiTag to the list of referenced tags of the group.
     *
     * @param mutlti_tag The MultiTag to add.
     */
    void addMultiTag(const MultiTag &multi_tag) {
        if (util::checkEntityInput(multi_tag, true)) {
            backend()->addEntity(multi_tag);
        }
    }

    /**
     * @brief Add a MultiTag to the list of referenced tags of the group.
     *
     * @param name_or_id    The name or id  of the MultiTag to add.
     */
    void addMultiTag(const std::string &name_or_id) {
        backend()->addEntity({name_or_id, ObjectType::MultiTag});
    }

    /**
     * @brief Remove a MultiTag from the list of referenced tags of the group.
     *
     * This method just removes the association between the tag and the
     * group, the tag itself will not be removed from the file.
     *
     * @param mulit_tag     The MultiTag to remove.
     *
     * @returns True if the MultiTag was removed, false otherwise.
     */
    bool removeMultiTag(const MultiTag &multi_tag) {
        if (!util::checkEntityInput(multi_tag, false)) {
            return false;
        }
        return backend()->removeEntity(multi_tag);
    }

    /**
     * @brief Remove a MultiTag from the list of referenced tags of the group.
     *
     * This method just removes the association between the tag and the
     * group, the MultiTag itself will not be removed from the file.
     *
     * @param name_or_id      The name or the id of the MultiTag to remove.
     *
     * @returns True if the MultiTag was removed, false otherwise.
     */
    bool removeMultiTag(const std::string &name_or_id) {
        return backend()->removeEntity({name_or_id, ObjectType::MultiTag});
    }

    /**
     * @brief Get referenced MultiTag associated with this group.
     *
     * The parameter filter can be used to filter MultiTag by various
     * criteria.
     *
     * @param filter    A filter function.
     *
     * @return A vector containing the matching tags.
     */
    std::vector<MultiTag> multiTags(const util::Filter<MultiTag>::type &filter) const;

    /**
     * @brief Get all referenced MultiTags associated with this group.
     *
     * Always uses filter that accepts all MultiTags.
     *
     * @return The filtered MultiTags as a vector
     */
    std::vector<MultiTag> multiTags() const {
        return multiTags(util::AcceptAll<MultiTag>());
    }

    /**
     * @brief Sets all referenced MultiTag entities.
     *
     * Previously referenced MultiTags, that are not in the passed vector
     * will be removed.
     *
     * @param mulit_tags    All MultiTags.
     */
    void multiTags(const std::vector<MultiTag> &multi_tags);


    /**
     * @brief Assignment operator for none.
     */
    Group &operator=(const none_t &t) {
        ImplContainer::operator=(t);
        return *this;
    }

    /**
     * @brief Output operator
     */
    NIXAPI friend std::ostream &operator<<(std::ostream &out, const Group &ent);

 private:
    template<typename T>
    void replaceEntities(const std::vector<T> &entitties);
};

template<>
struct objectToType<nix::Group> {
    static const bool isValid = true;
    static const ObjectType value = ObjectType::Group;
    typedef nix::base::IGroup backendType;
};

NIXAPI std::ostream &operator<<(std::ostream &out, const Group &ent);

} // namespace nix

#endif //NIX_GROUP_HPP
