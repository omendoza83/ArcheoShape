# ArcheoShape
## Analysis tools for geometric models of archaeological pieces

ArcheoShape is an open source project with software tools for modeling and analyzing archeological pieces. The current version has only one application written in C++ called <b>MeshAnalyzer</b>. Future versions will incorporate new tools developed in different languages.

<b>MeshAnalyzer</b> is a program with user interface that is used to compare 3D meshes. The intention of this program is to identify possible 3D meshes stored in a data base that are similar to one mesh provided by the user. The current version has an internal data set of more than 150 pre-processed meshes that represent prehispanic masks and other ancient tools. Incoming versions will allow to build and manage custom data bases.

To compile the project, you require the following libraries:

<ul>
  <li>QT 6.2 (<a href="https://www.qt.io">https://www.qt.io</a>)</li>
  <li>Eigen (<a href="https://eigen.tuxfamily.org">https://eigen.tuxfamily.org)</a></li>
</ul>

Additionally, you need to download the resource files of this project from <a href="https://github.com/omendoza83/ArcheoShape-Data">https://github.com/omendoza83/ArcheoShape-Data</a>. The resource files are required to compile the user interface as it contains images, preprocessed data and other important files.

This repository has one pre-compiled version of <b>MeshAnalyzer</b> for Windows. You can download it from the bin folder. 
