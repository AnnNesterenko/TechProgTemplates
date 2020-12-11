//
// Created by akhtyamovpavel on 5/1/20.
//


#include "TreeTestCase.h"
#include "Tree.h"
#include <filesystem>
#include <fstream>

namespace fs = std::__fs::filesystem;

TEST(TreeTest, PathNotExist){
    EXPECT_THROW(GetTree("akuna_matata", true), std::invalid_argument);
    EXPECT_THROW(GetTree("akuna_matata", false), std::invalid_argument);
}

TEST(TreeTest, NotDir){
    fs::path p = fs::current_path();
    p /= "akuna_matata.txt";
    std::ofstream ofs(p);
    ofs << "this is some text in the new file\n";
    ofs.close();

    EXPECT_THROW(GetTree(p, true), std::invalid_argument);
    EXPECT_THROW(GetTree(p, false), std::invalid_argument);

    fs::remove_all(p);
}

TEST(TreeTest, DirDepth1){
    fs::path p1 = fs::current_path();
    p1 /= "my_dir/text1.txt";
    fs::create_directories(p1.parent_path());

    std::ofstream ofs1(p1);
    ofs1 << "this is some text in the new file\n";
    ofs1.close();

    p1 = fs::current_path();
    p1 /= "my_dir";
    FileNode answer;
    answer.name = "my_dir";
    answer.is_dir = true;
    EXPECT_EQ(GetTree(p1, true), answer);

    FileNode child;
    child.name = "text1.txt";
    child.is_dir = false;
    answer.children.push_back(child);
    EXPECT_EQ(GetTree(p1, false), answer);

    fs::remove_all(fs::current_path() / "my_dir");
}

TEST(TreeTest, DirDepth2){
    fs::path p1 = fs::current_path();
    p1 /= "my_dir/my_dir2";
    fs::create_directories(p1);

    p1 = fs::current_path();
    p1 /= "my_dir";
    FileNode answer;
    answer.name = "my_dir";
    answer.is_dir = true;

    FileNode child;
    child.name = "my_dir2";
    child.is_dir = true;
    answer.children.push_back(child);
    EXPECT_EQ(GetTree(p1, true), answer);

    fs::remove_all(fs::current_path() / "my_dir");
}