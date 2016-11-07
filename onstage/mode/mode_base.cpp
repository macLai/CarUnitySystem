#include "mode_base.h"
#include "modeDB.h"
#include <qvariant.h>
#include <QDebug>

ModeBase::ModeBase(QString mode, QString modeDbData) :modeID(mode), currentView("")
{
	viewDB = new ModeDB(modeDbData);
	size = QSize(-1, -1);
}

bool ModeBase::startMode(QObject* target)
{
	displayTarget = target;
	size.setWidth(target->property("width").toInt());
	size.setHeight(target->property("height").toInt());
	return transTo("default");
};

bool ModeBase::transTo(QString target)
{
	if (!size.isValid()) return false;
	if (displayTarget == NULL) return false;

	QString viewPath = viewDB->getView(target, size.width(), size.height());
	if (viewPath == NULL) return false;

	QObject *loader = displayTarget->findChild<QObject *>(QString(), Qt::FindDirectChildrenOnly);
	if (loader == 0) return false;

	if (!loader->setProperty("source", viewPath)) return false;

	
	currentView = target;
	return true;
}

bool ModeBase::moveToPos(QObject* target)
{
	if (1)
	{
		displayTarget = target;
		size.setWidth(target->property("width").toInt());
		size.setHeight(target->property("height").toInt());
		return transTo(currentView);
	}
	return true;
}

bool ModeBase::endMode()
{
	displayTarget = NULL;
	currentView = "";
	size = QSize(-1, -1);
	return true;
}