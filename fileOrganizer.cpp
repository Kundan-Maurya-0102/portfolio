#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

using namespace std;

// Decide category based on file extension
string getCategory(const string& extension)
{
    // Documents
    if (extension == ".pdf" ||
        extension == ".doc" ||
        extension == ".docx" ||
        extension == ".txt" ||
        extension == ".ppt" ||
        extension == ".pptx" ||
        extension == ".xls" ||
        extension == ".xlsx")
    {
        return "Documents";
    }

    // Images
    if (extension == ".jpg" ||
        extension == ".jpeg" ||
        extension == ".png" ||
        extension == ".gif" ||
        extension == ".bmp" ||
        extension == ".webp")
    {
        return "Images";
    }

    // Videos
    if (extension == ".mp4" ||
        extension == ".mkv" ||
        extension == ".avi" ||
        extension == ".mov" ||
        extension == ".wmv")
    {
        return "Videos";
    }

    // Audio
    if (extension == ".mp3" ||
        extension == ".wav" ||
        extension == ".flac" ||
        extension == ".aac")
    {
        return "Audio";
    }

    // Programming files
    if (extension == ".cpp" ||
        extension == ".c" ||
        extension == ".h" ||
        extension == ".hpp" ||
        extension == ".py" ||
        extension == ".java" ||
        extension == ".js" ||
        extension == ".html" ||
        extension == ".css" ||
        extension == ".php")
    {
        return "Programming";
    }

    // Archives
    if (extension == ".zip" ||
        extension == ".rar" ||
        extension == ".7z" ||
        extension == ".tar" ||
        extension == ".gz")
    {
        return "Archives";
    }

    // Everything else
    return "Others";
}

int main()
{
    string folderPath;

    cout << "=====================================\n";
    cout << "       SMART FILE ORGANIZER\n";
    cout << "=====================================\n\n";

    cout << "Enter folder path: ";
    getline(cin, folderPath);

    fs::path folder(folderPath);

    // Check whether folder exists
    if (!fs::exists(folder) || !fs::is_directory(folder))
    {
        cout << "\nInvalid folder path!\n";
        return 1;
    }

    int movedFiles = 0;

    // Check files inside the folder
    for (const auto& entry : fs::directory_iterator(folder))
    {
        // Ignore directories
        if (!entry.is_regular_file())
            continue;

        fs::path filePath = entry.path();

        // Get file extension
        string extension = filePath.extension().string();

        // Get category
        string category = getCategory(extension);

        // Create category folder
        fs::path categoryFolder = folder / category;

        fs::create_directories(categoryFolder);

        // New file location
        fs::path newPath = categoryFolder / filePath.filename();

        try
        {
            // Move file
            fs::rename(filePath, newPath);

            cout << "Moved: "
                 << filePath.filename()
                 << " -> "
                 << category
                 << "\n";

            movedFiles++;
        }
        catch (const fs::filesystem_error& e)
        {
            cout << "Could not move: "
                 << filePath.filename()
                 << "\n";

            cout << "Reason: "
                 << e.what()
                 << "\n";
        }
    }

    cout << "\n=====================================\n";
    cout << "Organization completed!\n";
    cout << "Files moved: " << movedFiles << "\n";
    cout << "=====================================\n";

    return 0;
}