#pragma once

#include "types/String.h"
// #include "FileSystem.h"

class FileSystem;

class Path {

public:
    enum class PathType
    {
        Absolute,
        Relative,
        Invalid,
    };

    explicit Path(const String& path);
    explicit Path(const Vector<String>& parts, PathType);

    /**
     * e.g (/dev/keyboard, DevFS) => keyboard
     */
    bool remove_mount_prefix(const FileSystem& fs, Path& res) const;

    size_t num_parts() const {return m_parts.size();}
    const String& get_part(size_t idx) const {return m_parts[idx];}
    PathType type() const {return m_type;}

    Vector<String> parts_from_string(const String& path) const;
    PathType type_from_string(const String& path) const;

    String to_string() const;
    String base_name() const;

private:
    Vector<String> m_parts;
    PathType m_type;
};