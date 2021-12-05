
colorbar('off');
set(gcf,'PaperUnits','centimeter');
set(gcf,'PaperPosition',[0 0 5 4]);
axis('off')
getfeaturee();

function getfeaturee()
    getfeatures('pop',0);
    getfeatures('rock',1);
    getfeatures('metal',2);
    getfeatures('classical',3);
    getfeatures('reggae',4);
end

function getfeatures(name,label)
    folder=fullfile('genres_original',name);
    ads=audioDatastore(folder);
    adsTall=tall(ads);
    specsTall=cellfun(@(x)melSpectrogram(x,22050),adsTall,"UniformOutput",false);
    specs=gather(specsTall);
    for i=1:length(specs)
        S=cell2mat(specs(i));
        S=10*log10(S+eps);
        h=image(S,'CDataMapping','scaled');
        set(gca,'XTick',[],'YTick',[])
        dir=strcat('PruebaGaa/',name,'/',name,int2str(i),'.png');
        saveas(h,dir);
    end
end