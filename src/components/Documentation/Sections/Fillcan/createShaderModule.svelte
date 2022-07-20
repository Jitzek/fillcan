<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`std::unique_ptr<ShaderModule> createShaderModule(
        const std::string shaderDirectory, 
        const std::string shaderFileName,
        shaderc_shader_kind shaderKind,
        std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
        std::unique_ptr<DescriptorPool> upDescriptorPool, 
        bool preprocess = true,
        bool optimize = false\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a Shader Module object.<br />
        Uses <Anchor href="https://github.com/google/shaderc">Shaderc</Anchor> to
        compile a file (defined by <code>shaderDirectory</code> and
        <code>shaderFileName</code>) from <Anchor
            href="https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)"
            target="_blank">GLSL</Anchor
        > to <Anchor href="https://www.khronos.org/spir/" target="_blank"
            >SPIR-V</Anchor
        >. Any resources the shader might need should be passed using the
        descriptor set layouts and the descriptor pool, both are <Anchor
            href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
            target="_blank">unique pointers</Anchor
        > which ownerships should be moved to the Shader Module using <Anchor
            href="https://en.cppreference.com/w/cpp/utility/move"
            >std::move</Anchor
        >.
    </span>
    <div slot="params">
        <li>
            <code>shaderDirectory</code><br />
            The directory where the <Anchor
                href="https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)"
                target="_blank">GLSL</Anchor
            > shader file is located.
        </li>
        <li>
            <code>shaderFileName</code><br />
            The name of the <Anchor
                href="https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)"
                target="_blank">GLSL</Anchor
            > shader file.
        </li>
        <li>
            <code>shaderKind</code><br />
            The kind of shader (see <Anchor
                href="https://github.com/google/shaderc/blob/1bbf43f210941ba69a2cd05cf3529063f1ff5bb9/libshaderc/include/shaderc/shaderc.h#L36"
                target="_blank">shaderc.h line 36 - 90</Anchor
            >)
        </li>
        <li>
            <code>upDescriptorSetLayouts</code><br />
            A <Anchor
                href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
                target="_blank">unique pointer</Anchor
            > to a list of the <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.DESCRIPTOR_SET_LAYOUT}"
                >Descriptor Set Layouts</Anchor
            > describing the resources the shader should have access to. Please use
            <Anchor href="https://en.cppreference.com/w/cpp/utility/move"
                >std::move</Anchor
            > to transfer ownership. See <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER}"
                >DescriptorSetLayoutBuilder</Anchor
            > for creating <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.DESCRIPTOR_SET_LAYOUT}"
                >Descriptor Set Layouts</Anchor
            >.
        </li>
        <li>
            <code>upDescriptorPool</code><br />
            A unique pointer to the <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.DESCRIPTOR_POOL}"
                >Descriptor Pool</Anchor
            > where the <Anchor
                href="{getState().URL.documentation}#{SectionID.DESCRIPTOR_SET}"
                >Descriptor Sets</Anchor
            > can be retrieved from. Please use
            <Anchor href="https://en.cppreference.com/w/cpp/utility/move"
                >std::move</Anchor
            > to transfer ownership. See <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.DESCRIPTOR_POOL_BUILDER}"
                >DescriptorPoolBuilder</Anchor
            > for creating <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.DESCRIPTOR_POOL}"
                >Descriptor Pools</Anchor
            >.
        </li>
        <li>
            <code>preprocess</code><br />
            Whether to preprocess the shader to validate the <Anchor
                href="https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)"
                target="_blank">GLSL</Anchor
            > code. This will throw an exception if the shader failed to compile.
        </li>
        <li>
            <code>optimize</code><br />
            Whether the optimize the shader.
        </li>
    </div>
    <span slot="return">
        A unique pointer to the created <Reference
            sectionID={SectionID.SHADER_MODULE}>Shader Module</Reference
        > (ownership will be transferred to the implementation).
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Reference
            sectionID={SectionID.SHADER_MODULE}>Shader Module</Reference
        > couldn't be created.
    </span>
</MethodDescription><br />
Example:
<Highlight
    language={cppHighlight}
    code={`std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> upFragmentDescriptorSetLayouts = ...;
std::unique_ptr<fillcan::DescriptorPool> upFragmentDescriptorPool = ...;

std::unique_ptr<fillcan::ShaderModule> upVertexShaderModule =
    fillcan.createShaderModule(
        this->APP_DIR + "/shaders", 
        "shader.vert", 
        shaderc_vertex_shader, 
        {}, 
        nullptr, 
        true, 
        false\n);

std::unique_ptr<fillcan::ShaderModule> upFragmentShaderModule =
    fillcan.createShaderModule(
        this->APP_DIR + "/shaders", 
        "shader.frag", 
        shaderc_fragment_shader,
        std::move(upFragmentDescriptorSetLayouts), 
        std::move(upFragmentDescriptorPool), 
        true, 
        false\n);`}
/>
