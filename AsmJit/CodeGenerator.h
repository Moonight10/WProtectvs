
#ifndef _ASMJIT_CODEGENERATOR_H
#define _ASMJIT_CODEGENERATOR_H

#include "Build.h"

namespace AsmJit {

struct Assembler;
struct JitCodeGenerator;
struct MemoryManager;
struct MemoryMarker;

// ============================================================================
// [AsmJit::CodeGenerator]
// ============================================================================

//! @brief Code generator is core class for changing behavior of code generated
//! by @c Assembler or @c Compiler.
struct ASMJIT_API CodeGenerator
{
  CodeGenerator();
  virtual ~CodeGenerator();

  // --------------------------------------------------------------------------
  // [Interface]
  // --------------------------------------------------------------------------

  //! @brief Allocate memory for code generated in @a assembler and reloc it
  //! to target location.
  //!
  //! This method is universal allowing any pre-process / post-process work
  //! with code generated by @c Assembler or @c Compiler. Because @c Compiler
  //! always uses @c Assembler it's allowed to access only the @c Assembler
  //! instance.
  //!
  //! This method is always last step when using code generation. You can use
  //! it to allocate memory for JIT code, saving code to remote process or a 
  //! shared library.
  //!
  //! @retrurn Error value, see @c ERROR_CODE.
  virtual uint32_t generate(void** dest, Assembler* assembler) = 0;

  static JitCodeGenerator* getGlobal();

private:
  ASMJIT_DISABLE_COPY(CodeGenerator)
};

// ============================================================================
// [AsmJit::JitCodeGenerator]
// ============================================================================

struct JitCodeGenerator : public CodeGenerator
{
  // --------------------------------------------------------------------------
  // [Construction / Destruction]
  // --------------------------------------------------------------------------

  //! @brief Create a @c JitCodeGenerator instance.
  JitCodeGenerator();
  //! @brief Destroy the @c JitCodeGenerator instance.
  virtual ~JitCodeGenerator();

  // --------------------------------------------------------------------------
  // [Memory Manager and Alloc Type]
  // --------------------------------------------------------------------------

  // Note: These members can be ignored by all derived classes. They are here
  // only to privide default implementation. All other implementations (remote
  // code patching or making dynamic loadable libraries/executables) ignore
  // members accessed by these accessors.

  //! @brief Get the @c MemoryManager instance.
  inline MemoryManager* getMemoryManager() const { return _memoryManager; }
  //! @brief Set the @c MemoryManager instance.
  inline void setMemoryManager(MemoryManager* memoryManager) { _memoryManager = memoryManager; }

  //! @brief Get the type of allocation.
  inline uint32_t getAllocType() const { return _allocType; }
  //! @brief Set the type of allocation.
  inline void setAllocType(uint32_t allocType) { _allocType = allocType; }

  // --------------------------------------------------------------------------
  // [Memory Marker]
  // --------------------------------------------------------------------------

  //! @brief Get the @c MemoryMarker instance.
  inline MemoryMarker* getMemoryMarker() const { return _memoryMarker; }
  //! @brief Set the @c MemoryMarker instance.
  inline void setMemoryMarker(MemoryMarker* memoryMarker) { _memoryMarker = memoryMarker; }

  // --------------------------------------------------------------------------
  // [Interface]
  // --------------------------------------------------------------------------

  virtual uint32_t generate(void** dest, Assembler* assembler);

  // --------------------------------------------------------------------------
  // [Members]
  // --------------------------------------------------------------------------

protected:
  //! @brief Memory manager.
  MemoryManager* _memoryManager;
  //! @brief Memory marker.
  MemoryMarker* _memoryMarker;

  //! @brief Type of allocation.
  uint32_t _allocType;

private:
  ASMJIT_DISABLE_COPY(JitCodeGenerator)
};

} // AsmJit namespace

// [Guard]
#endif // _ASMJIT_CODEGENERATOR_H
