// diskimage.h : Disk image utilities headers

//////////////////////////////////////////////////////////////////////

/* Size of each RT-11 disk block, 512 or 0x200 bytes */
#define RT11_BLOCK_SIZE         512

#define NETRT11_IMAGE_HEADER_SIZE  256

struct CCachedBlock;

//////////////////////////////////////////////////////////////////////
// ����� ����� � ������� .dsk ���� .rtd

class CDiskImage
{
protected:
    FILE*           m_fpFile;
    bool            m_okReadOnly;
    bool            m_okNetRT11Image;
    int             m_nTotalBlocks;
    int             m_nCacheBlocks;  // Cache size in blocks
    CCachedBlock*   m_pCache;

public:
    CDiskImage();
    ~CDiskImage();

public:
    bool Attach(LPCTSTR sFileName);
    void Detach();

public:
    int IsReadOnly() const { return m_okReadOnly; }
    int GetBlockCount() const { return m_nTotalBlocks; }
    void* GetBlock(int nBlock);
    void MarkBlockChanged(int nBlock);
    void FlushChanges();

private:
    long GetBlockOffset(int nBlock) const;

};


//////////////////////////////////////////////////////////////////////
