#include "kmlweb.h"
#include "ui_kmlweb.h"

KMLWeb::KMLWeb(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::KMLWeb)
{
    ui->setupUi(this);
    //ui->kmlPathEntry->setText("C:/Users/Abdulmajed Dakkak/Documents/kml-web/debug/out.kml");
    //ui->htmlPathEntry->setText("C:/Users/Abdulmajed Dakkak/Documents/kml-web/debug/index.htm");
    //ui->pageTitleEntry->setText("Some title");
    //ui->pageDescriptionEntry->setPlainText("some sort of description");
}

KMLWeb::~KMLWeb()
{
    delete ui;
}

void KMLWeb::on_browseKMLButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
     tr("Open KML"), "", tr("KML Files (*.kml *.KML)"));
    ui->kmlPathEntry->setText(fileName);
}

void KMLWeb::on_browseHTMLButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
     tr("Save HTML"), "", tr("HTML Files (*.htm *.html)"));
    ui->htmlPathEntry->setText(fileName);
}

void KMLWeb::on_createButton_clicked()
{
    if (ui->createButton->text() == "Done")
    {
        QApplication::quit();
    }

    if (ui->kmlPathEntry->text() == "")
    {
        ui->kmlPathEntry->setText("Select KML File");
        return;
    }

    if (ui->htmlPathEntry->text() == "")
    {
        ui->htmlPathEntry->setText("Select HTML File");
        return;
    }

    QString inputKML = ui->kmlPathEntry->text();
    QString outputHTML = ui->htmlPathEntry->text();

    QString kmlBaseName = QFileInfo(inputKML).baseName();

    QString htmlContent = createHTML(ui->pageTitleEntry->text(),
                                     ui->pageDescriptionEntry->toPlainText(),
                                     kmlBaseName);
    QFile data(outputHTML);
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&data);
        out << htmlContent;
    }

    ui->createButton->setText("Done");
}

QString KMLWeb::createHTML(QString title, QString description, QString & kmlFileName)
{
    QString s = "<html>\n<head>\n";
    s += "	<title>" + title + "</title>\n";
     s += "	<style type=\"text/css\">\n";
     s += "		h1 {\n";
     s += "			font-family: \"courier\" \"Georgia\" ;\n";
     s += "			font-size: 45px;\n";
     s += "			margin-bottom: -20px;\n";
     s += "			text-align: center;\n";
     s += "		}\n";
     s += "		#map {\n";
     s += "		    width: 100%;\n";
     s += "		    height: 80%;\n";
     s += "		    border-top: 5px solid #333;\n";
     s += "		    border-bottom: 5px solid #333;\n";
     s += "		}\n";
     s += "		.olPopup p { margin:10px; padding:10px; font-size: .9em;}\n";
     s += "		.olPopup h2 { font-size:1.2em; }\n";
     s += "    	</style>\n";
     s += "	<script src=\"http://www.openlayers.org/api/OpenLayers.js\"></script>\n";
     s += "	<script src=\"http://www.openstreetmap.org/openlayers/OpenStreetMap.js\"></script>\n";
     s += "\n";
     s += "	<script type=\"text/javascript\">\n";
     s += "		var map, select;\n";
     s += "		function init() {\n";
     s += "			map = new OpenLayers.Map (\"map\", {\n";
     s += "				controls:[\n";
     s += "					new OpenLayers.Control.Navigation(),\n";
     s += "					new OpenLayers.Control.PanZoomBar(),\n";
     s += "					new OpenLayers.Control.ScaleLine()]\n";
     s += "			} );\n";
     s += "\n";
     s += "\n";
     s += "			\n";
     s += "			var osmLayer = new OpenLayers.Layer.OSM.Mapnik(\"Mapnik\");\n";
     s += "\n";
     s += "			\n";
     s += "			var symbolizer = OpenLayers.Util.applyDefaults(\n";
     s += "				{externalGraphic: \"http://www.google.com/intl/en_ALL/mapfiles/marker.png\", fillOpacity: 1, pointRadius: 10},\n";
     s += "				OpenLayers.Feature.Vector.style[\"default\"]);\n";
     s += "			var styleMap = new OpenLayers.StyleMap({\"default\": symbolizer, \"select\": {pointRadius: 30}});\n";
     s += "\n";
     s += "\n";
     s += "			var kmlData = new OpenLayers.Layer.GML(\"Data\", \""+ kmlFileName + ".kml\", {\n";
     s += "				format: OpenLayers.Format.KML, \n";
     s += "				styleMap: styleMap,\n";
     s += "				formatOptions: { extractAttributes: true }\n";
     s += "		        });\n";
     s += "	\n";
     s += "		    \n";
     s += "			map.addLayers([osmLayer,kmlData]);\n";
     s += "			    \n";
     s += "			select = new OpenLayers.Control.SelectFeature(kmlData);\n";
     s += "			    \n";
     s += "			kmlData.events.on({\n";
     s += "				\"featureselected\": onFeatureSelect,\n";
     s += "				\"featureunselected\": onFeatureUnselect\n";
     s += "			});\n";
     s += "\n";
     s += "			map.addControl(select);\n";
     s += "			select.activate();  \n";
     s += "			var lonLat = new OpenLayers.LonLat(0.0, 30.0).transform(new \n";
     s += "				OpenLayers.Projection(\"EPSG:4326\"), map.getProjectionObject()); \n";
     s += "			map.setCenter (lonLat, 2);\n";
     s += "        	}\n";
     s += "\n";
     s += "		\n";
     s += "		function onPopupClose(evt) {\n";
     s += "		    select.unselectAll();\n";
     s += "		}\n";
     s += "		function onFeatureSelect(event) {\n";
     s += "		    var feature = event.feature;\n";
     s += "		    var content = feature.attributes.description;\n";
     s += "		    popup = new OpenLayers.Popup.FramedCloud(\"chicken\", \n";
     s += "		                             feature.geometry.getBounds().getCenterLonLat(),\n";
     s += "		                             new OpenLayers.Size(100,100),\n";
     s += "		                             content,\n";
     s += "		                             null, true, onPopupClose);\n";
     s += "		    feature.popup = popup;\n";
     s += "		    map.addPopup(popup);\n";
     s += "		}\n";
     s += "		function onFeatureUnselect(event) {\n";
     s += "		    var feature = event.feature;\n";
     s += "		    if(feature.popup) {\n";
     s += "		        map.removePopup(feature.popup);\n";
     s += "		        feature.popup.destroy();\n";
     s += "		        delete feature.popup;\n";
     s += "		     }\n";
     s += "		}\n";
     s += "	</script>\n";
     s += "</head>\n";
     s += "\n";
     s += "<body onload=\"init();\">\n";
     s += "	<h1 id=\"title\">"+ title + "</h1>\n";
     s += "	<hr/>\n";
     s += "	<div  id=\"map\"></div>\n";
     s += "	<hr/>\n";
     s += "	<p>" + description + " </p>";
     s += "</body>\n";
     s += "</html>\n";
     s += "\n";
     s += "\n";
    return s;
}
