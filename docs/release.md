# Release Checklist

Use this checklist before tagging a YJDragGrid release.

## Version

- Update `project(YJDragGrid VERSION ...)` in `CMakeLists.txt`.
- Update `CHANGELOG.md` and move `Unreleased` entries under the new version.
- Confirm the release follows semantic versioning.

## Verification

```bash
cmake -S . -B build -DYJDRAGGRID_BUILD_EXAMPLES=OFF
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
cmake --install build --prefix build/install
```

Also verify a consumer project can use the installed package:

```cmake
find_package(YJDragGrid CONFIG REQUIRED)
target_link_libraries(Consumer PRIVATE YJDragGrid::YJDragGrid)
```

## GitHub Release

- Push the release commit.
- Create and push an annotated tag.
- Draft a GitHub Release from the changelog entry.
- Attach relevant screenshots or preview GIF updates when UI behavior changed.
