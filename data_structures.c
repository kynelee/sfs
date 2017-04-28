/* Data structures for representing SFS */


/* Provides metadata for the file system
 * The super block is the first portion of the file which 
 * represents our entire file system. 
 * It contains pointers to the start of the inode, 
 * block map, and actual disk block, memory regions. 
 * SuperBlock is used to find available blocks, and index into
 * inodes/blocks. 
 */
struct SuperBlock { 
  const void * inode_start; // pointer to start of inodes 
  const int inode_size; // size of each inode

  const void * single_map_start;  // pointer to start of single_maps
  const int single_map_size;  // size of each single maps

  const void * double_map_start;  // pointer to start of double map 
  const int doublee_map_size;  // size of each double map 

  const int * block_start; // start of of memory blocks 
  const int * block_size;  // size in bytes of each block 
  const int * block_num;  // number of blocks

  Block free_blocks[block_num]; // array of pointers of free blocks  TODO Might need to change this to linked list 
  int free_blocks_count; // count of how many free blocks are available
}



/* A block struct represents all the data about a block 
 * of memory. Each block corresponds to one file, and may be partially
 * filled. Each file corresponds to an inode, which corresponds to a
 * list of (potentially non-contiguous) blocks
*/ 
struct Block {
  const int block_id;  // which block number (0...block_count) this corresponds to 
  const void * block_pointer: // which memory address this block is located
  const void * filled; // how much of this block is filled
}



/* A single map represents a fixed size list of block 
 * structs. These structs, when concatenated in order, represent the file. 
 */
struct SingleMap {
  Block blocks[single_map_size]; // Contains a list of blocks
}

/* A double map represents a fixed size list of single map 
 * structs. T
 */
struct DoubleMap {
  SingleMap maps[double_map_size];
}


/* An Inode represents a file. 
 * To store the files data itself, each inode has a fixed number of 
 * directly mapped blocks, another constant number of single maps which point to lists of blocks, 
 * and a number of double maps which point to lists of single maps
 * Inodes allocate blocks first directly mapped, then single mapped, 
 * then double mapped (until the size of each runs out). 
 * 
 * An Inode also stores file metadata information, such as the name,
 * position relative to other files, and 
 */

struct INode {
  enum type; // Either directory, file, or link? 

  // Data - only relevant if file
  Block direct_mapped_blocks[NUM_DIRECT]//  list of direct mapped blocks. 
  SingleMap * single_mapped_blocks[NUM_SINGLE_MAP]; // list of lists of direct mapped blocks.
  DoubleMap * double_mapped_blocks[NUM_DOUBLE_MAP]; // list of lists of lists of direct mapped blocks.


  // File Metadata and Location  
  char * path;


  // Directory Specific information
  INode ** children; // List of children  
  INode * parent; // Parent to this directory 
}
