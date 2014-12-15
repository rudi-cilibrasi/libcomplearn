#ifndef __NCDITERATORTYPE_H
#define __NCDITERATORTYPE_H

enum NCDIteratorType {
  NCDIteratorTypeDirectory,
  NCDIteratorTypeFilenameList,
  NCDIteratorTypeSingleFile
};

enum NCDIteratorStepType {
  NCDDataAndLabels = 0,
  NCDNoData = 1,
  NCDNoLabels = 2,
  NCDNoDataNorLabels = 3
};

#endif
