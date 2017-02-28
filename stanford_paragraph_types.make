core = 7.x
api = 2

; https://www.drupal.org/node/2786271 | Patch adds search_index view mode.
projects[paragraphs][version] = "1.0-rc4"
projects[paragraphs][subdir] = "contrib"
projects[paragraphs][patch][] = "https://www.drupal.org/files/issues/search-index-view-modes-2786271-5.patch"

projects[blockreference][version] = "2.4"
projects[blockreference][subdir] = "contrib"

projects[chosen][version] = "2.0"
projects[chosen][subdir] = "contrib"

libraries[chosen][download][type] = "git"
libraries[chosen][download][url] = "https://github.com/harvesthq/chosen/releases/download/v1.6.2/chosen_v1.6.2.zip"
libraries[chosen][directory_name] = "chosen"
libraries[chosen][destination] = "libraries"