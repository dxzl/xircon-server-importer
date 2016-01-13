Copyright 2015 Scott Swift - This program is distributed under the
terms of the GNU General Public License.

Use Borland's C++ Builder 4 to compile. The free compiler can probably
compile it but I've never tried http://edn.embarcadero.com/article/21205

My C++ Builder Tools->Environment Options Library Path:
$(BCB)\Lib;
$(BCB)\Bin;
$(BCB)\Imports;
$(BCB)\Projects\Lib;
$(BCB)\PROJECTS\Bpl;

My ServerImporter Project Include path:
ServerImporter;$(BCB)\include;$(BCB)\include\vcl

My ServerImporter Project Library path:
ServerImporter;$(BCB)\Projects\Lib;$(BCB)\lib\obj;$(BCB)\lib

More info and files on the XiRCON IRC Chat Client:
http://yahcolorize.com/#XiRCON
