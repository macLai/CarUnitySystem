#include "mode_base.h"
#include "modeDB.h"
#include <qvariant.h>
#include <QDebug>
#include <qpropertyanimation.h>

ModeBase::ModeBase(QString mode, QString modeDbData, QObject *loader) :modeID(mode), currentView(""), displayTarget(loader)
{
	showAnime = new QPropertyAnimation(loader, "opacity");
	showAnime->setDuration(500);
	showAnime->setEndValue(1);
	hideAnime = new QPropertyAnimation(loader, "opacity");
	hideAnime->setDuration(500);
	hideAnime->setEndValue(0);

	viewDB = new ModeDB(modeDbData);
	pos = QRect(0, 0, 400, 480);
	startMode();
}

bool ModeBase::startMode()
{
	return transTo("default");
};

bool ModeBase::transTo(QString target)
{
	displayTarget->setProperty("opacity", 1);
	if (!pos.size().isValid()) return false;
	if (displayTarget == NULL) return false;

	QString viewPath = viewDB->getView(target, pos.width(), pos.height());
	if (viewPath == NULL) return false;

	if (!displayTarget->setProperty("source", viewPath)) return false;

	
	currentView = target;
	return true;
}

bool ModeBase::moveToPos(QRect rect)
{
	if (pos == rect && displayTarget->property("opacity") == 1) return true;

	pos = rect;
	if (displayTarget->property("opacity") != 0)
	{
		connect(hideAnime, SIGNAL(finished()), this, SLOT(setProperty()));
		hideAnime->start();
	}
	else
	{
		setProperty();
	}
	return true;
}

bool ModeBase::endMode()
{
	hideAnime->start();
	return true;
}

bool ModeBase::setProperty()
{
	disconnect(hideAnime, SIGNAL(finished()), this, SLOT(setProperty()));

	int x = displayTarget->property("x").toInt();
	int y = displayTarget->property("y").toInt();
	int width = displayTarget->property("width").toInt();
	int height = displayTarget->property("height").toInt();

	if (pos.width() != width || pos.height() != height)
	{
		displayTarget->setProperty("width", pos.width());
		displayTarget->setProperty("height", pos.height());

		QString viewPath = viewDB->getView(currentView, pos.width(), pos.height());
		if (viewPath != NULL)
		{
			displayTarget->setProperty("source", viewPath);
		}
	}
	displayTarget->setProperty("x", pos.x());
	displayTarget->setProperty("y", pos.y());

	showAnime->start();
	return true;
}