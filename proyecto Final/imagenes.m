
digitDatasetPath=fullfile('imagenesmatlab');

    imds=imageDatastore(digitDatasetPath,'IncludeSubfolders',true,'LabelSource','foldernames');
    numTrainFiles=75;
    [imdsTrain,imdsValidation]=splitEachLabel(imds,numTrainFiles,'randomize');
    inputSize=[288,432,3];
    numClasses=5;
    
    layers=[imageInputLayer([236 295 3])
    convolution2dLayer([5 5],16,'Padding',[2 2 2 2],'Stride',2)
    reluLayer
    maxPooling2dLayer(2,'Stride',2)
    
    convolution2dLayer([3 3],32,'Stride',2)
    reluLayer
    maxPooling2dLayer(4,'Stride',2)
    
    batchNormalizationLayer
    dropoutLayer(0.6)
    fullyConnectedLayer(1000);
     dropoutLayer(0.2)
    fullyConnectedLayer(500);
    fullyConnectedLayer(numClasses);
    softmaxLayer
    classificationLayer];

options=trainingOptions('sgdm','MaxEpochs',30,'ValidationData',imdsValidation,'InitialLearnRate',0.0001,'Shuffle','every-epoch','ValidationFrequency',5,'Verbose',true,'L2Regularization',0.003,'Plots','training-progress','MiniBatchSize',32);

net=trainNetwork(imdsTrain,layers,options);

YPred=classify(net,imdsValidation);
YValidation=imdsValidation.Labels;
accuracy=mean(YPred==YValidation);

