##projet
with project("NKCore"):
    language("C++")
    cppdialect("C++20")
    

    nkentseudependson(
        ["NKPlatform"],
        selfexport="NKCore",
        extra_includes=["src", "pch"],
    )

    pchheader("pch/pch.h")
    pchsource("pch/pch.cpp")

    files([
        "src/NKCore/**.cpp",
        "src/NKCore/**.h",
    ])

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}") ?
    targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}") ?

    with filter("system:Windows && options:windows-runtime=uwp"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-uwp") ?

    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
        usetoolchain(TC_WINDOWS) ?
    with filter("system:UWP || system:Windows && options:windows-runtime=uwp"):
        usetoolchain("xbox-clang") ?
