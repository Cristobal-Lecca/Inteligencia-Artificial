figure('Units','normalized','Position',[0.2 0.2 0.4 0.4]);
cm=confusionchart(YValidation,YPred);
cm.Title='Confusion Matrix for Valitadion Data';
cm.ColumnSummary='column-normalized';
cm.RowSummary='row-normalized';