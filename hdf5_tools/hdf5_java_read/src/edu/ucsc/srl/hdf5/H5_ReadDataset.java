package edu.ucsc.srl.hdf5;

import ncsa.hdf.hdf5lib.H5; 
import ncsa.hdf.hdf5lib.HDF5Constants; 

public class H5_ReadDataset  
{ 
  static final int dimX = 4;
  static final int dimY = 7;
  static final String DATASETNAME = "DS1";

  private static void testPathLookup() throws Exception
  {
    String mappedName = "";
    try {
      String s_libraryName = "jhdf5";
      mappedName = System.mapLibraryName(s_libraryName);
      System.out.println("mappedName: " + mappedName);
      System.loadLibrary(mappedName);
      boolean isLibraryLoaded = true;
    }
    catch (Throwable err) {
      err.printStackTrace();
      boolean isLibraryLoaded = false;
    }


  }
  private static void ReadDataset(String inFile) throws Exception 
  { 
    int file_id = -1;
    int dataset_id = -1;
    int[][] dset_data = new int[dimX][dimY];

    try {
      file_id = H5.H5Fopen(inFile, HDF5Constants.H5F_ACC_RDONLY, 
                           HDF5Constants.H5P_DEFAULT);
    } catch ( Exception e ) { 
      e.printStackTrace();
    }

    try { 
      if (file_id >=0)
        dataset_id = H5.H5Dopen(file_id, DATASETNAME, HDF5Constants.H5P_DEFAULT);
    } catch ( Exception e ) {
      e.printStackTrace();
    }

    try {
      if (dataset_id >= 0)
        H5.H5Dread(dataset_id, HDF5Constants.H5T_NATIVE_INT,
                  HDF5Constants.H5S_ALL, HDF5Constants.H5S_ALL,
                  HDF5Constants.H5P_DEFAULT, dset_data);
    } catch ( Exception e ) {
      e.printStackTrace();
    }

    // write the data out
    System.out.println(DATASETNAME + ":");
    for ( int index = 0; index < dimX; index++) { 
      System.out.println("[");
      for( int jndex = 0; jndex < dimY; jndex++) { 
        System.out.println(dset_data[index][jndex] + " ");
      }
      System.out.println("]");
    }
    System.out.println();

    // close the dataset
    try{ 
      if(dataset_id >= 0)
        H5.H5Dclose(dataset_id);
    } catch ( Exception e) {
      e.printStackTrace();
    }

    // close the file
    try { 
      if (file_id >= 0)
        H5.H5Fclose(file_id);
    } catch (Exception e) { 
      e.printStackTrace();
    }
  } 

  public static void main(String[] args)  
  { 
    String inFile;
    if ( args.length < 1) {
      System.out.println("No file path specified. Try again");
      return;
    } else {
      inFile = args[0];
    }
    try { 
      H5_ReadDataset.ReadDataset(inFile); 
    } catch (Exception e) {  
      e.printStackTrace();  
    } 
  } 
}
