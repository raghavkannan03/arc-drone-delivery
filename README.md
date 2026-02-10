# ARC Drone Delivery - Monorepo

This is the unified monorepo for Purdue's Autonomous Robotics Club (ARC) Drone Delivery project. All drone delivery subsystems have been consolidated here for easier development and collaboration.

## 📄 Documentation

Please refer to the `Documentation` folder for project docs, guides, and technical references.

## 📁 Repository Structure

```
arc-drone-delivery/
├── navigation-stack/     # Core ROS 2 Navigation Workspace (DD_Nav_WS)
├── onboarding/           # Tutorial and onboarding materials
├── avoidance-viz/        # Obstacle avoidance visualization tool
├── path-planning/        # Path planning and SLAM algorithms
├── obstacle-avoidance/   # C++ Intel RealSense obstacle avoidance
├── octree-generator/     # Octree generation for mapping
└── operations-website/   # Solid-start frontend operations website
```

## 🚀 Quick Start

Each subdirectory contains its own README with specific setup instructions. Here's a brief overview:

### Navigation Stack
**Path**: `navigation-stack/`  
**Purpose**: Core ROS 2 workspace for drone navigation, PX4 integration, and Gazebo simulation  
**Key Features**: GPS global mapping, Nav2 implementation, PX4 flight controller integration  
**Setup**: See [navigation-stack/README.md](navigation-stack/README.md)

### Onboarding
**Path**: `onboarding/`  
**Purpose**: Comprehensive tutorial for new team members  
**Topics**: Git workflow, ROS 2 basics, Gazebo simulation, publisher/subscriber patterns  
**Setup**: See [onboarding/README.md](onboarding/README.md)

### Avoidance Visualization
**Path**: `avoidance-viz/`  
**Purpose**: Visualization tool for obstacle avoidance verification  
**Setup**: See [avoidance-viz/README.md](avoidance-viz/README.md)

### Path Planning
**Path**: `path-planning/`  
**Purpose**: Path planning algorithms including A*, D*, and Dijkstra  
**Language**: C++  
**Setup**: See [path-planning/README.md](path-planning/README.md)

### Obstacle Avoidance
**Path**: `obstacle-avoidance/`  
**Purpose**: Real-time obstacle detection using Intel RealSense cameras  
**Platform**: Windows with Visual Studio  
**Setup**: See [obstacle-avoidance/README.md](obstacle-avoidance/README.md)

### Octree Generator
**Path**: `octree-generator/`  
**Purpose**: Generate octree representations for 3D mapping  
**Setup**: See [octree-generator/](octree-generator/)

### Operations Website
**Path**: `operations-website/`  
**Purpose**: Web-based drone operations dashboard with CesiumJS 3D visualization  
**Tech Stack**: Solid.js, Solid Start, Material UI (SUID), Nhost, PostgreSQL  
**Features**: Manual drone control, flight monitoring, delivery operations  
**Setup**: See [operations-website/README.md](operations-website/README.md)

## 🤖 AI Coding Assistants (Recommended)

To help you understand and contribute to this large codebase, we **strongly recommend** using AI coding assistants:

### GitHub Copilot
- **Free for students**: Get a free subscription with your `.edu` email
- **Sign up**: [GitHub Student Developer Pack](https://education.github.com/pack)
- **Features**: Code completion, chat, and explanations directly in VS Code

### Google AI Pro (Gemini)
- **Free tier**: 1 year of Google AI Pro with your education email
- **Sign up**: [Google for Education](https://edu.google.com/intl/ALL_us/workspace-for-education/)
- **Features**: Advanced code understanding, debugging assistance, and documentation generation
- Download Google Antigravity IDE and sign in

These tools are invaluable for:
- Understanding unfamiliar ROS 2 concepts
- Debugging complex C++ and Python code
- Learning the PX4 flight controller API
- Navigating this large monorepo structure

## 🛠️ Development Workflow

### Prerequisites
- **ROS 2 Humble** (for navigation-stack, onboarding)
- **Ubuntu 22.04** (recommended for ROS components)
- **Node.js** (for operations-website)
- **Python 3** (for various scripts)
- **Visual Studio** (for obstacle-avoidance on Windows)

### Building Components

Each component has its own build system:
- **ROS packages**: Use `colcon build` in the workspace directory
- **C++ projects**: Use `make` or Visual Studio
- **Website**: Use `npm install` and `npm run dev`

## 📝 Contributing

1. Create a feature branch from `main`
2. Make your changes in the appropriate subdirectory
3. Test thoroughly
4. Submit a pull request with a clear description

## 🧹 Monorepo Migration Notes

This monorepo was created on **February 1, 2026** by consolidating 7 individual repositories:
- Removed 121 accidentally-committed build log files from navigation-stack
- Cleaned git history to improve clone performance
- Maintained logical separation of components in subdirectories

### Original Repositories
- [`DD_Nav_WS`](https://github.com/purdue-arc/DD_Nav_WS) → `navigation-stack/`
- [`DD_On_Boarding`](https://github.com/purdue-arc/DD_On_Boarding) → `onboarding/`
- [`dd-avoidance-visualization`](https://github.com/purdue-arc/dd-avoidance-visualization) → `avoidance-viz/`
- [`dd-navigation`](https://github.com/purdue-arc/dd-navigation) → `path-planning/`
- [`DD-obstacle-avoidance`](https://github.com/purdue-arc/DD-obstacle-avoidance) → `obstacle-avoidance/`
- [`dd-octree_generator`](https://github.com/purdue-arc/dd-octree_generator) → `octree-generator/`
- [`drone-delivery-website`](https://github.com/purdue-arc/drone-delivery-website) → `operations-website/`

### ⚠️ Important: Accessing Old Branches and Large Files

**Specialized Branches Not in Monorepo:**
The following branches were **not** migrated to preserve a clean monorepo:
- `DD_Nav_WS`: `px4`, `px4-twist`, `px4-test`, `nav2_implementation`, `teleop`, `gps_global_mapping`
- `DD_On_Boarding`: `simulation_dev`
- `dd-navigation`: `SLAM_Main`
- `dd-octree_generator`: `demonstration-of-bad-voxels`
- `drone-delivery-website`: `docker-testing`, `geography_point_change`, `supabase-integration`

**To access these branches:**
1. Clone the original GitHub repositories: `https://github.com/purdue-arc/[repo-name]`
2. Checkout the specific branch you need
3. Cherry-pick commits into the monorepo if needed

**Git LFS Large Files:**
The following large files are stored in Git LFS and were **not** included in the monorepo:
- `Purdue_map.dae` (977 MB) - Purdue campus 3D model
- `purdue_map.gltf` - Purdue campus GLTF format
- `test_world.dae` - Gazebo test world file

**To access LFS files:**
1. Clone the original `DD_Nav_WS` repository from GitHub
2. Run `git lfs pull` to download the large files
3. Copy them to your local monorepo if needed (they're gitignored)

## 📚 Resources

- [Purdue ARC Website](https://purduearc.com/)
- [ROS 2 Documentation](https://docs.ros.org/en/humble/)
- [PX4 Autopilot](https://px4.io/)
- [Gazebo Simulation](https://gazebosim.org/)