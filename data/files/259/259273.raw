using NIfTI, MAT
files=filter(r".nii.gz",readdir());
for i=1:length(files)
name=files[i];
nii=niread(name);
file=matopen(replace(name,".nii.gz",".mat"),"w");
write(file,"data",nii.raw);
write(file,"header",nii.header);
write(file,"voxel_size",voxel_size(nii.header));
write(file,"time_step",time_step(nii.header));
#write(file,"extensions",nii.extensions);
close(file);
end
