# TODO

- [ ] Shape
  - [ ] Sphere
  - [ ] Cylinder
  - [ ] Disk
  - [ ] Cone
  - [ ] Paraboloid
  - [ ] Hyperboloid
  - [ ] Mesh
  - [ ] Curve
- [ ] Accelerator
  - [ ] BVH
  - [ ] KDTree
- [X] Spectrum
  - [ ] CoefficientSpectrum
    - [ ] SampledSpectrum
    - [X] RGBSpectrum
- [X] Camera
  - [X] ProjectiveCamera
    - [X] OrthographicCamera
    - [X] PerspectiveCamera
  - [ ] EnvironmentCamera
  - [ ] RealisticCamera
- [ ] Sampler
  - [ ] RandomSampler
  - [ ] PixelSampler
    - [ ] StratifiedSampler
    - [ ] ZeroTwoSequenceSampler
    - [ ] MaxMinDistSampler
  - [ ] GlobalSampler
    - [ ] HaltonSampler
    - [ ] SobolSampler
- [X] Filter
  - [X] BoxFilter
  - [X] TriangleFilter
  - [X] GaussianFilter
  - [X] MitchellFilter
  - [X] LanczosSincFilter
- [X] Fresnel
  - [X] FresnelConductor
  - [X] FresnelDielectrics
  - [ ] FresnelNoOp
- [X] MicrofacetDistribution
  - [ ] BeckmannSpizzichinoDistribution
  - [ ] TrowbridgeReitzDistribution
- [X] BxDF
  - [X] SpecularReflection
  - [X] SpecularTransmission
  - [X] FresnelSpecular
  - [X] LambertianReflection
  - [X] LambertianTransmission
  - [X] OrenNayar
  - [X] MicrofacetReflection
  - [X] MicrofacetTransmission
  - [ ] FresnelBlend
  - [ ] FourierBSDF
- [ ] Material
  - [ ] MatteMaterial
  - [ ] PlasticMaterial
  - [ ] MixMaterial
  - [ ] FourierMaterial
  - [ ] GlassMaterial
  - [ ] MetalMaterial
  - [ ] MirrorMaterial
  - [ ] SubstrateMaterial
  - [ ] SubsurfaceMaterial
  - [ ] TranslucentMaterial
  - [ ] UberMaterial
- [ ] TextureMapping2D
  - [ ] UVMapping2D
  - [ ] SphericalMapping2D
  - [ ] CylindricalMapping2D
  - [ ] PlanarMapping2D
- [ ] TextureMapping3D
  - [ ] TransformMapping3D
- [ ] Texture
  - [ ] ConstantTexture
  - [ ] ScaleTexture
  - [ ] MixTexture
  - [ ] BilerpTexture
  - [ ] ImageTexture
  - [ ] UVTexture
  - [ ] Checkerboard2DTexture
  - [ ] Checkerboard3DTexture
  - [ ] DotsTexture
  - [ ] FBmTexture
  - [ ] WrinkledTexture
  - [ ] WindyTexture
  - [ ] MarbleTexture
- [ ] Medium
  - [ ] HomogeneousMedium
  - [ ] GridDensityMedium
- [ ] BSSRDF
  - [ ] SeparableBSSRDF
  - [ ] TabulatedBSSRDF
- [ ] Light
  - [ ] PointLight
  - [ ] SpotLight
  - [ ] ProjectionLight
  - [ ] GonioPhotometricLight
  - [ ] DistantLight
  - [ ] AreaLight
    - [ ] DiffuseAreaLight
  - [ ] InfiniteAreaLight
- [ ] Integrator
  - [ ] SamplerIntegrator
    - [ ] AOIntegrator
    - [ ] WhittedIntegrator
    - [ ] DirectLightingIntegrator
    - [ ] PathIntegrator
    - [ ] VolPathIntegrator
  - [ ] BDPTIntegrator
  - [ ] SPPMIntegrator
  - [ ] MLTIntegrator