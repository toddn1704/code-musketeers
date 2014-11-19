/*shoppinglist.cpp

This file will implement the functions declared in the
shoppinglist.h file.

*/

#include "shoppinglist.h"
#include "qmessagebox.h"
#include <fstream>
#include <Shlobj.h>
Shoppinglist::Shoppinglist(QWidget *parent,std::vector<std::string> output)
	: QDialog(parent)
{
	ui.setupUi(this);
	//connect(ui.export_button, SIGNAL(itemted()), this, SLOT(ExportList()));
	for (int i = 0; i < output.size(); i++)
	{
		output_.append(output[i]);
		output_.append("\n");
	}
	ui.items_textedit->setText(QString::fromStdString(output_));
}

void Shoppinglist::on_export_button_clicked()
{
	qDebug() << "export clicked.";
	wchar_t *d_path = 0;
	SHGetKnownFolderPath(FOLDERID_Desktop,
						0,
						NULL,
						&d_path);
	size_t origsize = wcslen(d_path) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	char desktop_path[newsize];
	wcstombs_s(&convertedChars, desktop_path, origsize, d_path, _TRUNCATE);
	strcat(desktop_path, "\\Shopping_List.txt");
	qDebug() << desktop_path;
	std::ofstream output_file;
	output_file.open(desktop_path,std::ofstream::out);
	output_file << output_;
	output_file.close();
}