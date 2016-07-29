#include "romfs.hpp"
#include <iostream>

RomFsDisk::RomFsDisk(u8 *file) : fileStart(file), fileSystemHeader(file) {
    fileSystemHeader.readInfo();
    firstFileHeader = fileSystemHeader.getHeaderEnd();
}

File RomFsDisk::openFile(const std::string &filePath) {
    auto directoryStart = firstFileHeader;
    File file;
    auto files = getFilesArray(filePath);
    for (int i = 0; i < files.size(); i++) {
        auto fileHeader = findFileHeaderIntoDir(directoryStart, files[i]);
        if (!fileHeader.isExist()) {
            return file;
        }
        if (fileHeader.getFileType() != FileType::DIRECTORY &&
            i != files.size() - 1) {
            return file;
        }
        if (i != files.size() - 1)
            directoryStart = fileStart + fileHeader.getSpecInfo();
        else {
            if (fileHeader.getFileType() != FileType::REGULAR_FILE) {
                return file;
            }
            directoryStart = fileHeader.getStartPtr();
        }
    }
    FileHeader fHdr(directoryStart);
    fHdr.readFile();

    file.fileHdr.setMemoryStart(directoryStart);
    file.fileHdr.readFile();
    file.open = true;
    return file;
}

std::vector<std::string>
RomFsDisk::getAllFileNamesInDir(const std::string &directoryPath) {
    auto directoryStart = firstFileHeader;
    std::vector<std::string> filesList;

    auto files = getFilesArray(directoryPath);
    for (int i = 0; i < files.size(); i++) {
        std::cout << "szukam: " << files[i] << std::endl;
        auto fileHeader = findFileHeaderIntoDir(directoryStart, files[i]);
        if (!fileHeader.isExist()) {
            std::cout << "file not exist" << std::endl;
            return filesList;
        }
        if (fileHeader.getFileType() != FileType::DIRECTORY) {
            return filesList;
        }
        directoryStart = fileStart + fileHeader.getSpecInfo();
    }
    FileHeader fHdr(directoryStart);

    auto filePtr = directoryStart;
    while (filePtr != nullptr) {
        FileHeader fHdr(filePtr);
        fHdr.readFile();
        std::string name = fHdr.getName();
        filesList.push_back(name);
        auto offset = fHdr.getAlignedNextFileOffset();
        if (0 == offset) {
            filePtr = nullptr;
        } else {
            filePtr = fileStart + offset;
        }
    }
    return filesList;
}

FileHeader RomFsDisk::findFileHeaderIntoDir(u8 *directoryStart,
                                            const std::string &fileName) {
    auto filePtr = directoryStart == nullptr ? firstFileHeader : directoryStart;
    while (filePtr != nullptr) {
        FileHeader fHdr(filePtr);
        fHdr.readFile();
        if (fileName == fHdr.getName()) {
            return fHdr;
        }
        auto offset = fHdr.getNextFileOffset();
        if (0 == offset) {
            filePtr = nullptr;
        } else {
            filePtr = fileStart + offset;
        }
    }
    return FileHeader(nullptr);
}
