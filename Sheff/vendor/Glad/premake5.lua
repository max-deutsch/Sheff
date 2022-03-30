project "Glad"
    kind "StaticLib" -- What is a static library exactly?
    language "C"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs -- what does this mean? The include dirs for this project. So when adding other files it looks at this dir?
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"    