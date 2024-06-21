// Copyright Karnakhall


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;	// Set the WidgetController to the InWidgetController
	WidgetControllerSet();	// Call the WidgetControllerSet function
}
